//===----------------------------------------------------------------------===//
// Copyright (c) 2020 Polar. All rights reserved.
// https://getathena.ml
//
// Licensed under MIT license.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.
//===----------------------------------------------------------------------===//

#include "PolarGraph/PolarGraphDialect.h"
#include "PolarGraph/PolarGraphOps.h"
#include "Passes/Passes.h"

#include "mlir/Dialect/StandardOps/IR/Ops.h"
#include "mlir/IR/Module.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/DialectConversion.h"

using namespace mlir;

static uint64_t getNodeResultingTensorAddres(polar_graph::NodeOp node) {
  Operation* op = node.getBody().front().getTerminator();

  while (!llvm::isa<polar_graph::CreateTensorOp>(op)) {
    op = op->getOperand(op->getNumOperands() - 1).getDefiningOp();
  }

  auto tensorOp = llvm::cast<polar_graph::CreateTensorOp>(op);
  // fixme is it safe?
  return *tensorOp.virtual_address().getRawData();
}

namespace {

struct EvalOpRewriter : OpRewritePattern<polar_graph::EvalOp> {
  using OpRewritePattern<polar_graph::EvalOp>::OpRewritePattern;

  LogicalResult matchAndRewrite(polar_graph::EvalOp evalOp,
                                PatternRewriter& rewriter) const override {
    auto module = evalOp.getParentOfType<ModuleOp>();
    auto node = module.lookupSymbol<polar_graph::NodeOp>(evalOp.node());
    rewriter.replaceOpWithNewOp<polar_graph::EvalOp>(evalOp, node, ValueRange{});
    return success();
  };
};
struct NodeOpRewriter : mlir::ConversionPattern {
  explicit NodeOpRewriter(MLIRContext* context)
      : ConversionPattern(polar_graph::NodeOp::getOperationName(), 1, context) {}
  LogicalResult
  matchAndRewrite(Operation* op, ArrayRef<Value> operands,
                  ConversionPatternRewriter& rewriter) const override {
    auto nodeOp = llvm::cast<polar_graph::NodeOp>(op);

    auto oldArgsCount = nodeOp.getNumArguments();
    auto newType = rewriter.getFunctionType({}, nodeOp.getType().getResults());

    auto newNode = nodeOp.clone();
    newNode.setType(newType);

    rewriter.insert(newNode);
    TypeConverter::SignatureConversion newSignature(oldArgsCount);

    rewriter.applySignatureConversion(&newNode.getBody(), newSignature);
    rewriter.eraseOp(nodeOp);

    return success();
  }
};

class RelationDestructorPass
    : public PassWrapper<RelationDestructorPass, OperationPass<ModuleOp>> {
protected:
  void runOnOperation() override {
    auto module = getOperation();

    // Step 1. Replace all arguments with tensor creation commands.
    module.walk([](polar_graph::EvalOp evalOp) {
      if (evalOp.getNumOperands()) {
        for (auto curOp : llvm::enumerate(evalOp.getOperands())) {
          auto operand = curOp.value();
          auto parentEval =
              llvm::cast<polar_graph::EvalOp>(operand.getDefiningOp());
          auto module = evalOp.getParentOfType<ModuleOp>();
          auto parentNode =
              module.lookupSymbol<polar_graph::NodeOp>(parentEval.node());
          auto tensorId = getNodeResultingTensorAddres(parentNode);

          auto callableNode =
              module.lookupSymbol<polar_graph::NodeOp>(evalOp.node());
          OpBuilder builder(module);
          builder.setInsertionPointToStart(&callableNode.getBody().front());
          auto newTensor = builder.create<polar_graph::CreateTensorOp>(
              builder.getUnknownLoc(), tensorId,
              operand.getType().cast<RankedTensorType>());
          callableNode.getBody()
              .front()
              .getArgument(curOp.index())
              .replaceAllUsesWith(newTensor);
        }
      }
    });

    OwningRewritePatternList patterns;
    patterns.insert<NodeOpRewriter>(&getContext());
    patterns.insert<EvalOpRewriter>(&getContext());
    ConversionTarget target(getContext());
    target.addDynamicallyLegalOp<polar_graph::EvalOp>(
        [](polar_graph::EvalOp op) { return op.getNumOperands() == 0; });
    target.addDynamicallyLegalOp<polar_graph::NodeOp>(
        [](polar_graph::NodeOp op) { return op.getType().getNumInputs() == 0; });
    if (failed(applyPartialConversion(getOperation(), target, patterns))) {
      signalPassFailure();
    }
  }
};
} // namespace

namespace mlir {
std::unique_ptr<OperationPass<ModuleOp>> createGraphRelationDestructorPass() {
  return std::make_unique<RelationDestructorPass>();
}
} // namespace mlir

/*
 * Copyright (c) 2019 Athena. All rights reserved.
 * https://athenaframework.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include "common.h"

namespace athena::backend::llvm::codegen {

::llvm::Function *create_ffill_decl(::llvm::LLVMContext &ctx,
                                    ::llvm::Module &module) {
    std::vector<::llvm::Type *> args(2, ::llvm::Type::getInt64Ty(ctx));
    args.push_back(::llvm::Type::getFloatTy(ctx));
    ::llvm::FunctionType *FT =
        ::llvm::FunctionType::get(::llvm::Type::getVoidTy(ctx), args, false);

    ::llvm::Function *F = ::llvm::Function::Create(
        FT, ::llvm::Function::ExternalLinkage, "athena_ffill", &module);

    return F;
}

void registerFill(LLVMGenerator *generator) {
    std::function<void(::llvm::LLVMContext &, ::llvm::Module &,
                       ::llvm::IRBuilder<> &, core::inner::Tensor &, void *&)>
        f = [generator](::llvm::LLVMContext &ctx, ::llvm::Module &module,
                        ::llvm::IRBuilder<> &builder, core::inner::Tensor &a,
                        void *&filler) {
            // todo handle different data types

            ::llvm::Function *calledFunction =
                module.getFunction("athena_ffill");

            if (!calledFunction)
                calledFunction = create_ffill_decl(ctx, module);

            if (!calledFunction) {
                core::FatalError(1, "Unknown function referenced");
            }

            std::vector<::llvm::Value *> ArgsV;
            ::llvm::Constant *allocatorConst =
                ::llvm::ConstantInt::get(::llvm::Type::getInt64Ty(ctx),
                                         (size_t)(&generator->getAllocator()));
            ArgsV.push_back(allocatorConst);
            ::llvm::Constant *tensorConst = ::llvm::ConstantInt::get(
                ::llvm::Type::getInt64Ty(ctx), (size_t)(&a));
            ArgsV.push_back(tensorConst);
            ::llvm::Constant *fillerConst =
                ::llvm::ConstantFP::get(::llvm::Type::getFloatTy(ctx),
                                        *reinterpret_cast<float *>(filler));
            ArgsV.push_back(fillerConst);
            builder.CreateCall(calledFunction, ArgsV);
        };
    generator->registerFunctor("fill", f);
}
}  // namespace athena::backend::llvm::codegen

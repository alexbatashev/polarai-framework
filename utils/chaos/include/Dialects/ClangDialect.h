//===----------------------------------------------------------------------===//
// Copyright (c) 2020 Athena. All rights reserved.
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

#ifndef ATHENA_CLANGDIALECT_H
#define ATHENA_CLANGDIALECT_H

#include "mlir/IR/Dialect.h"
#include "mlir/IR/Function.h"
#include "mlir/IR/Module.h"

namespace clang {
class ClangDialect : public mlir::Dialect {
public:
  explicit ClangDialect(mlir::MLIRContext* ctx);

  /// Provide a utility accessor to the dialect namespace. This is used by
  /// several utilities for casting between dialects.
  static llvm::StringRef getDialectNamespace() { return "clang"; }

  mlir::Type parseType(mlir::DialectAsmParser& parser) const override;
  void printType(mlir::Type type,
                 mlir::DialectAsmPrinter& printer) const override;
};

using namespace mlir;

namespace detail {
struct StructTypeStorage;
struct RawPointerTypeStorage;
} // namespace detail
namespace ClangMLIRTypes {
enum Types {
  Struct = mlir::Type::FIRST_PRIVATE_EXPERIMENTAL_0_TYPE,
  Pointer = mlir::Type::FIRST_PRIVATE_EXPERIMENTAL_1_TYPE
};
}

class StructType : public mlir::Type::TypeBase<StructType, mlir::Type,
                                               detail::StructTypeStorage> {
public:
  using Base::Base;
  static bool kindof(unsigned kind) { return kind == ClangMLIRTypes::Struct; }
  static StructType get(llvm::ArrayRef<mlir::Type> memberTypes);
  llvm::ArrayRef<mlir::Type> getMemberTypes();
  size_t getNumMemberTypes() { return getMemberTypes().size(); }
};

class RawPointerType
    : public mlir::Type::TypeBase<RawPointerType, mlir::Type,
                                  detail::RawPointerTypeStorage> {
public:
  using Base::Base;
  static bool kindof(unsigned kind) { return kind == ClangMLIRTypes::Pointer; }
  static RawPointerType get(mlir::Type pointee);
  mlir::Type getPointeeType();
};

#define GET_OP_CLASSES
#include <Dialects/ClangDialect.h.inc>
} // namespace clang

#endif // ATHENA_CLANGDIALECT_H

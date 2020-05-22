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

#include "AthenaGraph/AthenaGraphDialect.h"
#include "AthenaGraph/AthenaGraphOps.h"

using namespace mlir;
using namespace mlir::ath_graph;

AthenaGraphDialect::AthenaGraphDialect(mlir::MLIRContext* context)
    : Dialect(getDialectNamespace(), context) {
  addOperations<
#define GET_OP_LIST
#include "AthenaGraph/AthenaGraphOps.cpp.inc"
      >();
}
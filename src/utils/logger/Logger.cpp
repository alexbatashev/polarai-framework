//===----------------------------------------------------------------------===//
// Copyright (c) 2020 PolarAI. All rights reserved.
//
// Licensed under MIT license.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.
//===----------------------------------------------------------------------===//

#include <polarai/utils/error/FatalError.hpp>
#include <polarai/utils/logger/Logger.hpp>

namespace polarai::utils {
#ifdef DEBUG
namespace internal {
void debugLoggerFatalError() {
  FatalError(ATH_BAD_ACCESS, "Stream is nullptr.");
}
} // namespace internal
#endif
} // namespace polarai::utils

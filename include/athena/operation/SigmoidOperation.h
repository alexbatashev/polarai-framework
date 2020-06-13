/*
 * Copyright (c) 2018 Athena. All rights reserved.
 * https://getathena.ml
 *
 * Licensed under MIT license.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#ifndef ATHENA_SIGMOIDOPERATION_H
#define ATHENA_SIGMOIDOPERATION_H

#include <athena/core/operation/Operation.h>
#include <athena/operation/internal/SigmoidOperationInternal.h>
#include <athena/operation/operation_export.h>

namespace athena::operation {
class ATH_OPERATION_EXPORT SigmoidOperation : public core::Operation {
public:
using InternalType = internal::SigmoidOperationInternal;
enum Arguments { Unmarked=50 };
};
} // namespace athena::operation

#endif // ATHENA_SIGMOIDOPERATION_H

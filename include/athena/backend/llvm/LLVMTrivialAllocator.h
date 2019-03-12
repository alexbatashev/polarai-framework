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

#ifndef ATHENA_LLVMTRIVIALALLOCATOR_H
#define ATHENA_LLVMTRIVIALALLOCATOR_H

#include <athena/core/Allocator.h>
#include <athena/core/Tensor.h>

#include <unordered_map>

namespace athena::backend::llvm {
class LLVMTrivialAllocator : public athena::core::Allocator {
    private:
    std::unordered_map<size_t, void*> mAllocatedMap;
    std::allocator<uint8_t> mAllocator;

    public:
    void allocate(const athena::core::Tensor&) override;
    size_t getRAMPointer() override;
    size_t getFastPointer(const athena::core::Tensor&) override;
};
}  // namespace athena::backend::llvm

#endif  // ATHENA_LLVMTRIVIALALLOCATOR_H

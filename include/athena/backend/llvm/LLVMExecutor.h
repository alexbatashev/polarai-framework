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

#ifndef ATHENA_LLVMEXECUTOR_H
#define ATHENA_LLVMEXECUTOR_H

#include <athena/backend/llvm/BackendAllocator.h>
#include <athena/backend/llvm/llvm_export.h>
#include <athena/backend/llvm/runtime/Device.h>
#include <athena/core/graph/Traversal.h>
#include <athena/core/internal/Executor.h>
#include <athena/core/loader/internal/TensorAllocator.h>

namespace athena::backend::llvm {

// Forward declarations
class AthenaJIT;
class RuntimeDriver;

/// Default device filter. Selects all devices.
constexpr auto DefaultDeviceFilter = [](std::shared_ptr<Device>&) {
  return true;
};

/**
 * Execute Graph with LLVM-based backend
 */
class ATH_BACKEND_LLVM_EXPORT LLVMExecutor
    : public athena::core::internal::Executor {
public:
  using FilterFunctionT = std::function<bool(std::shared_ptr<Device>&)>;
  LLVMExecutor(bool enableDebugOutput = false,
               FilterFunctionT filter = DefaultDeviceFilter);

  /// Adds Graph to compilable module.
  ///
  /// \param graph is a valid Graph to be compiled.
  void addGraph(athena::core::Graph& graph) override;

  /// Executes particular graph.
  ///
  /// \param graph is a valid Graph, that has been previously added.
  void evaluate(athena::core::Graph& graph) override;

  BackendAllocator& getAllocator();
  std::shared_ptr<BackendAllocator> getAllocatorPtr();
  void setAllocator(std::shared_ptr<BackendAllocator>& allocator);

  std::vector<std::shared_ptr<Device>>& getDevices();

  void addModule(std::string_view module);

  void execute(std::string_view name, void* userData);

private:
  FilterFunctionT mFilter;
  // Driver must come first to ensure proper shutdown
  std::shared_ptr<RuntimeDriver> mRuntimeDriver;
  std::vector<std::shared_ptr<Device>> mDevices;

  std::shared_ptr<AthenaJIT> mJITCompiler{nullptr};
  std::shared_ptr<BackendAllocator> mAllocator;
};
} // namespace athena::backend::llvm

#endif // ATHENA_LLVMEXECUTOR_H

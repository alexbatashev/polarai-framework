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

#pragma once

#include <polarai/core/context/internal/Edge.hpp>
#include <polarai/core/graph/Traversal.hpp>
#include <polarai/core/tensor/internal/TensorInternal.hpp>
#include <polarai/utils/Index.hpp>
#include <polarai/utils/allocator/Allocator.hpp>
#include <polarai/utils/internal/TupleContainers.hpp>
#include <polarai/utils/storages/HeterogeneousVector.hpp>
#include <polar_core_export.h>

#include <unordered_map>
#include <vector>

namespace polarai::core::internal {

struct InternalIndex {
  utils::Index vectorIndex;
  utils::Index localIndex;
};

using Container = std::vector<utils::HeterogeneousVector<Entity>>;

using Map = std::unordered_map<utils::Index, InternalIndex>;

class POLAR_CORE_EXPORT ContextInternal {
public:
  explicit ContextInternal(utils::Allocator<utils::byte> allocator,
                           size_t defaultCapacity, size_t elementAverageSize);

  ~ContextInternal();

  // TODO restrict some types (by SFINAE?)
  template <typename InternalType, typename... Args>
  utils::Index create(Args&&... args);

  utils::Allocator<utils::byte>& getAllocator();

  const Traversal& traverse(utils::Index publicGraphIndex);

  template <typename Type> const Type& get(utils::Index publicIndex) const;

  template <typename Type> Type& getRef(utils::Index publicIndex);

  template <typename Type> const Type& getRef(utils::Index publicIndex) const;

  template <typename Type> const Type* getPtr(utils::Index publicIndex) const;

  template <typename Type> Type* getPtr(utils::Index publicIndex);

  utils::Index getNextPublicIndex() const;

  utils::Index registerTensor(const TensorInternal& tensor);

private:
  utils::Allocator<utils::byte> mAllocator;
  Container mContainer;
  Map mPublicIndexToPrivateIndex;
  utils::Index mInstancesCounter;
  utils::Index mNextTensorVirtualAddress;
};

// TODO restrict some types (by SFINAE?)
template <typename InternalType, typename... Args>
utils::Index ContextInternal::create(Args&&... args) {
  auto& backVector = mContainer.back();
  utils::Index resLocalIndex = 0, resVectorIndex = mContainer.size() - 1;
  auto localInstancesCounter = mInstancesCounter++;
  if (backVector.isAbleToContain<InternalType>()) {
    resLocalIndex =
        backVector.emplaceBack<InternalType>(std::forward<Args>(args)...);
  } else {
    mContainer.emplace_back(
        backVector.calculateRequiredCapacity(sizeof(InternalType)),
        backVector.elementAverageSize(), mAllocator);
    resVectorIndex = mContainer.size() - 1;
    resLocalIndex = mContainer.back().emplaceBack<InternalType>(
        std::forward<Args>(args)...);
  }
  mPublicIndexToPrivateIndex[localInstancesCounter] =
      InternalIndex{resVectorIndex, resLocalIndex};
  return localInstancesCounter;
}

template <typename Type>
const Type& ContextInternal::get(utils::Index publicIndex) const {
  auto internalIndex = mPublicIndexToPrivateIndex.at(publicIndex);
  return mContainer[internalIndex.vectorIndex].get<Type>(
      internalIndex.localIndex);
}

template <typename Type>
Type& ContextInternal::getRef(utils::Index publicIndex) {
  auto internalIndex = mPublicIndexToPrivateIndex.at(publicIndex);
  return mContainer[internalIndex.vectorIndex].get<Type>(
      internalIndex.localIndex);
}

template <typename Type>
const Type& ContextInternal::getRef(utils::Index publicIndex) const {
  auto internalIndex = mPublicIndexToPrivateIndex.at(publicIndex);
  return mContainer[internalIndex.vectorIndex].get<Type>(
      internalIndex.localIndex);
}

template <typename Type>
const Type* ContextInternal::getPtr(utils::Index publicIndex) const {
  auto internalIndex = mPublicIndexToPrivateIndex.at(publicIndex);
  return &(mContainer[internalIndex.vectorIndex].get<Type>(
      internalIndex.localIndex));
}

template <typename Type>
Type* ContextInternal::getPtr(utils::Index publicIndex) {
  auto internalIndex = mPublicIndexToPrivateIndex.at(publicIndex);
  return &(mContainer[internalIndex.vectorIndex].get<Type>(
      internalIndex.localIndex));
}
} // namespace polarai::core::internal

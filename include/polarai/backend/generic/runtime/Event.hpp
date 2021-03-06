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

#include <functional>

namespace polarai::backend::generic {
class Device;
class Event {
public:
  virtual ~Event() = default;
  virtual void wait() = 0;
  virtual void addCallback(std::function<void()>) = 0;
  virtual auto getDevice() -> Device* = 0;
};
} // namespace polarai::backend::generic

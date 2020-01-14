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

#ifndef ATHENA_DRIVER_H
#define ATHENA_DRIVER_H

#include <athena/chaos/driver.h>
#include <string>
#include <vector>

class CHAOS_DRIVER_EXPORT Driver {
private:
  std::string exec(const std::string& cmd);

public:
  void run(int argc, char** argv);
};

#endif // ATHENA_DRIVER_H
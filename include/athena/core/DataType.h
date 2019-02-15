/*
 * Copyright (c) 2018 Athena. All rights reserved.
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

#ifndef ATHENA_DATATYPE_H
#define ATHENA_DATATYPE_H

#include <cstddef>

namespace athena::core {
enum class DataType : int {
    DOUBLE = 0,
    FLOAT = 1,
    HALF = 2
};

size_t sizeOfDataType(const DataType& dataType);
}

#endif //ATHENA_DATATYPE_H
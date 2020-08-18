/**
 * MIT License
 *
 * Copyright (c) 2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STEP_DATA_HEADER
#define STEP_DATA_HEADER

#include <string>
#include <variant>
#include <vector>

#include "step_api.hpp"
#include "step_types.hpp"

namespace step::detail {

/**
 * The Data class is a helper that represents either GID or Base64 tile data.
 *
 * @since 0.1.0
 */
class Data final {
 public:
  using GIDData = std::vector<global_id>;
  using Base64Data = std::string;

  STEP_API
  explicit Data(const json& json);

  /**
   * Returns the GID data associated with the Data instance. This method
   * throws an exception if the internal data isn't actually GID data.
   *
   * @return the GID data associated with the Data instance.
   * @throws step_exception if the data cannot be obtained.
   * @since 0.1.0
   */
  STEP_QUERY
  const GIDData& as_gid() const;

  /**
   * Returns the Base64 data associated with the Data instance. This method
   * throws an exception if the internal data isn't actually Base64 data.
   *
   * @return the Base64 data associated with the Data instance.
   * @throws step_exception if the data cannot be obtained.
   * @since 0.1.0
   */
  STEP_QUERY
  const Base64Data& as_base64() const;

 private:
  std::variant<GIDData, Base64Data> m_data;
};

}  // namespace step::detail

#endif  // STEP_DATA_HEADER

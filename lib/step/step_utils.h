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

#ifndef STEP_UTILS_HEADER
#define STEP_UTILS_HEADER

#include <charconv>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "step_api.h"
#include "step_color.h"
#include "step_exception.h"
#include "step_types.h"

namespace step::detail {

/**
 * Parses the specified JSON file and returns the data associated with the
 * file as a JSON object.
 *
 * @param file the the JSON file that will be parsed.
 * @return a JSON object that contains the data from the parsed file.
 * @throws StepException if the file cannot be parsed.
 * @since 0.1.0
 */
[[nodiscard]] STEP_API JSON parse_json(std::string_view file);

template <typename T>
void bind_maybe(const JSON& json, std::string_view key, Maybe<T>& attribute)
{
  if (json.contains(key)) {
    attribute = json.at(key.data()).get<T>();
  }
}

template <typename T>
void safe_bind(const JSON& json, std::string_view key, T& value)
{
  if (json.contains(key)) {
    json.at(key.data()).get_to(value);
  }
}

/**
 * Attempts to convert a string to an integral value.
 *
 * @tparam T the integral type that will be used.
 * @param str the string that represents the integer.
 * @param base the base that will be used, defaults to 10.
 * @return the integral value.
 * @throws StepException if the string cannot be converted.
 * @since 0.1.0
 */
template <typename T>
[[nodiscard]] T convert(std::string_view str, int base = 10)
{
  T result{};
  if (const auto [ptr, error] =
          std::from_chars(str.data(), str.data() + str.size(), result, base);
      error != std::errc::invalid_argument &&
      error != std::errc::result_out_of_range) {
    return result;
  } else {
    throw StepException{"Failed to convert string to integral!"};
  }
}

template <typename T>
[[nodiscard]] constexpr bool valid_property_type() noexcept
{
  return std::is_same_v<T, bool> || std::is_same_v<T, int> ||
         std::is_same_v<T, float> || std::is_same_v<T, Color> ||
         std::is_convertible_v<T, std::string>;
}

}  // namespace step::detail

#ifdef STEP_HEADER_ONLY
#include "step_utils.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_UTILS_HEADER

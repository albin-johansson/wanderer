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
#include <memory>
#include <named_type.hpp>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "step_api.hpp"
#include "step_color.hpp"
#include "step_exception.hpp"
#include "step_types.hpp"

namespace step::detail {

/**
 * Parses the specified JSON file and returns the data associated with the
 * file as a JSON object.
 *
 * @param file the the JSON file that will be parsed.
 * @return a JSON object that contains the data from the parsed file.
 * @throws step_exception if the file cannot be parsed.
 * @since 0.1.0
 */
[[nodiscard]] STEP_API json parse_json(std::string_view file);

template <typename T>
void bind_opt(const json& json,
              std::string_view key,
              std::optional<T>& attribute)
{
  if (json.contains(key)) {
    attribute = json.at(key.data()).get<T>();
  }
}

template <typename T>
void emplace_opt(const json& json,
                 const std::string& key,
                 std::optional<T>& attribute)
{
  if (json.contains(key)) {
    attribute.emplace(json.at(key));
  }
}

template <typename T>
void safe_bind(const json& json, std::string_view key, T& value)
{
  if (json.contains(key)) {
    json.at(key.data()).get_to(value);
  }
}

template <typename T>
T safe_get(const json& json, const std::string& key, T defaultValue = {})
{
  static_assert(
      std::is_default_constructible_v<T>,
      "The type must be default constructible in order to use safe_bind!");
  if (json.contains(key)) {
    return json.at(key).get<T>();
  } else {
    return defaultValue;
  }
}

template <typename T>
[[nodiscard]] std::unique_ptr<T> safe_bind_unique(const json& json,
                                                  const std::string& key)
{
  if (json.contains(key)) {
    return std::make_unique<T>(json.at(key));
  } else {
    return nullptr;
  }
}

template <typename T>
void emplace(const json& json, const std::string& key, T& value)
{
  if (json.contains(key)) {
    value = json.at(key);
  }
}

template <typename Container>
[[nodiscard]] Container fill(const json& json, const std::string& key)
{
  Container container;
  for (const auto& [key, value] : json.at(key).items()) {
    container.emplace_back(value);
  }
  return container;
}

template <typename Container>
[[nodiscard]] Container fill(const json& json)
{
  Container container;
  for (const auto& [key, value] : json.items()) {
    container.emplace_back(value);
  }
  return container;
}

/**
 * Creates a vector of unique pointers where every element has a constructor
 * that takes a single <code>const JSON&</code> parameter.
 *
 * @tparam Type the type of the elements.
 * @param json the JSON object that holds the data.
 * @param key the key of the array that holds the objects.
 * @return a vector of unique pointers.
 * @since 0.1.0
 */
template <typename Type>
[[nodiscard]] auto fill_unique_vec(const json& json, const std::string& key)
{
  std::vector<std::unique_ptr<Type>> container;
  container.reserve(json.size());
  for (const auto& [_, value] : json.at(key).items()) {
    container.emplace_back(std::make_unique<Type>(value));
  }
  return container;
}

/**
 * Attempts to convert a string to an integral value.
 *
 * @tparam T the integral type that will be used.
 * @param str the string that represents the integer.
 * @param base the base that will be used, defaults to 10.
 * @return the integral value.
 * @throws step_exception if the string cannot be converted.
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
    throw step_exception{"Failed to convert string to integral!"};
  }
}

template <typename T>
[[nodiscard]] constexpr bool valid_property_type() noexcept
{
  return std::is_same_v<T, bool> || std::is_same_v<T, int> ||
         std::is_same_v<T, float> || std::is_same_v<T, color> ||
         std::is_same_v<T, file> || std::is_convertible_v<T, std::string>;
}

}  // namespace step::detail

#endif  // STEP_UTILS_HEADER

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

#ifndef STEP_PROPERTIES_HEADER
#define STEP_PROPERTIES_HEADER

#include <algorithm>   // for_each
#include <functional>  // less
#include <map>
#include <string>
#include <string_view>

#include "step_api.hpp"
#include "step_color.hpp"
#include "step_property.hpp"
#include "step_types.hpp"
#include "step_utils.hpp"

namespace step {

/**
 * @class properties
 *
 * @brief Represents a collection of `property` instances.
 *
 * @see property
 *
 * @since 0.1.0
 */
class properties final {
 public:
  STEP_API
  explicit properties(const json& json);

  /**
   * @brief Iterates over all of the properties store in this instance.
   *
   * @tparam Lambda the type of the lambda object.
   *
   * @param lambda the lambda that takes one argument, `std::pair<std::string,
   * Property>`, either by value or const reference.
   *
   * @since 0.1.0
   */
  template <typename Lambda>
  void each(Lambda&& lambda) const
  {
    std::for_each(m_properties.cbegin(), m_properties.cend(), lambda);
  }

  /**
   * @brief Indicates whether or not there is a property associated with the
   * specified name.
   *
   * @param name the name of the property to look for.
   *
   * @return `true` if there is a property associated with the specified name;
   * `false` otherwise.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto has(std::string_view name) const -> bool;

  /**
   * @brief Returns the property associated with the specified name.
   *
   * @note This method will throw an exception if the desired property doesn't
   * exist.
   *
   * @param name the name of the desired property.
   *
   * @return the property associated with the specified name.
   *
   * @throws `step_exception` if the desired property doesn't exist.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto get(std::string_view name) const -> const property&;

  /**
   * @brief Indicates whether or not the specified property is equal to the
   * supplied value.
   *
   * @details This method does not throw any exceptions by itself and is the
   * preferred way to check the value of a property. The returned value is
   * always `false` if the property doesn't exist or if the property has another
   * type.
   *
   * @details A compile-time error will be raised if the type of the
   * supplied value isn't one of: `bool`, `int`, `float`, `color`, `file` or
   * `std::string` (accepts anything that is convertible to `std::string`).
   *
   * @tparam T the type of the value that will be compared to the value of
   * the specified property. An unsupported type will cause a compile-time
   * error.
   *
   * @param name the name of the property to check the value of.
   * @param value the value that will be compared with the value of the
   * specified property.
   *
   * @return `true` if the specified property had a value and it turned out to
   * be equal to the supplied value; `false` otherwise.
   *
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto is(std::string_view name, const T& value) const -> bool
  {
    if (!has(name)) {
      return false;
    }
    const auto& property = get(name);
    return property.is<T>();
  }

  /**
   * @brief Returns the amount of `property` instances handled by this instance.
   *
   * @return the amount of properties handled by this instance.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto amount() const noexcept -> int;

  /**
   * @brief Indicates whether or not there are any `property` instances handled
   * by this instance.
   *
   * @return `true` if there are properties handled by this instance; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto empty() const noexcept -> bool;

 private:
  std::map<std::string, property, std::less<>> m_properties;
};

}  // namespace step

#endif  // STEP_PROPERTIES_HEADER

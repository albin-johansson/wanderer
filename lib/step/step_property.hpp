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

#ifndef STEP_PROPERTY_HEADER
#define STEP_PROPERTY_HEADER

#include <string>
#include <type_traits>
#include <variant>

#include "step_api.hpp"
#include "step_color.hpp"
#include "step_types.hpp"
#include "step_utils.hpp"
#include "step_valid_property.hpp"

namespace step {

/**
 * @class property
 *
 * @brief Represents small objects that have a name, type and value.
 *
 * @details A property can represent a `std::string`, `int`, `float`, `bool`,
 * `color` or `file`.
 *
 * @since 0.1.0
 *
 * @headerfile step_property.hpp
 */
class property final {
 public:
  /**
   * @enum type
   *
   * @brief Provides different values that represent the various kinds of
   * possible property types.
   *
   * @since 0.1.0
   *
   * @headerfile step_property.hpp
   */
  enum class type {
    string,    ///< For string values, such as `"foo"`.
    integer,   ///< For integer values, e.g. `27`.
    floating,  ///< For floating-point values, e.g. `182.4`.
    boolean,   ///< For the boolean values `true`/`false`.
    color,     ///< For ARGB/RGB colors, e.g. `"AARRGGBB"` and `"RRGGBB"`.
    file,      ///< For file paths, e.g. `"some/path/abc.png"`.
    object     ///< For referencing other objects. Really just an integer ID.
  };

  explicit property(const json& json)
      : m_name{json.at("name").get<std::string>()},
        m_type{json.at("type").get<property::type>()}
  {
    switch (m_type) {
      case property::type::integer: {
        m_value.emplace<int>(json.at("value").get<int>());
        break;
      }
      case property::type::floating: {
        m_value.emplace<float>(json.at("value").get<float>());
        break;
      }
      case property::type::boolean: {
        m_value.emplace<bool>(json.at("value").get<bool>());
        break;
      }
      case property::type::color: {
        m_value.emplace<color>(json.at("value").get<std::string>());
        break;
      }
      case property::type::file: {
        m_value.emplace<file>(json.at("value").get<std::string>());
        break;
      }
      case property::type::object: {
        m_value.emplace<object_ref>(json.at("value").get<int>());
        break;
      }
      case property::type::string: {
        m_value.emplace<std::string>(json.at("value").get<std::string>());
        break;
      }
      default:
        throw step_exception{"Unknown property type!"};
    }
  }

  /**
   * @brief Returns the value of the property as the specified type.
   *
   * @note This method will throw an exception if the property doesn't contain
   * the specified type.
   *
   * @details A compile-time error will be raised if the type of the supplied
   * value isn't one of: `bool`, `int`, `float`, `color`, `file` or
   * `std::string` (accepts anything that is convertible to `std::string`).
   *
   * @tparam T the type of the value that will be returned. Must be the same
   * type of the value stored in the property. An unsupported type will cause a
   * compile-time error.
   *
   * @return the value of the property.
   *
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto get() const -> const T&
  {
    return std::get<T>(m_value);
  }

  /**
   * @brief Attempts to return the value of the property as the specified type.
   *
   * @note This method doesn't throw any exceptions on its own.
   *
   * @details If the property doesn't contain a value of the specified type,
   * then the supplied default value is returned instead.
   *
   * @details A compile-time error will be raised if the type of the supplied
   * value isn't one of: `bool`, `int`, `float`, `color`, `file` or
   * `std::string` (accepts anything that is convertible to `std::string`).
   *
   * @tparam T the type of the value that will be obtained. An unsupported type
   * will cause a compile-time error.
   *
   * @param defaultValue the backup value that will be returned if the
   * desired value cannot be obtained.
   *
   * @return the value stored in the property; `defaultValue` if the property
   * doesn't contain a value of the specified type.
   *
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto get_or(const T& defaultValue) const -> const T&
  {
    if (is<T>()) {
      return get<T>();
    } else {
      return defaultValue;
    }
  }

  /**
   * @brief Indicates whether or not the property holds a value of the specified
   * type.
   *
   * @details A compile-time error will be raised if the type of the supplied
   * value isn't one of: `bool`, `int`, `float`, `color`, `file` or
   * `std::string` (accepts anything that is convertible to `std::string`).
   *
   * @tparam T the type to compare with the type of the stored value. An
   * unsupported type will cause a compile-time error.
   *
   * @return `true` if the property holds a value of the specified type; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto is() const noexcept -> bool
  {
    if constexpr (std::is_same_v<T, bool>) {
      return m_type == type::boolean;

    } else if constexpr (std::is_same_v<T, int>) {
      return m_type == type::integer;

    } else if constexpr (std::is_same_v<T, float>) {
      return m_type == type::floating;

    } else if constexpr (std::is_same_v<T, color>) {
      return m_type == type::color;

    } else if constexpr (std::is_same_v<T, file>) {
      return m_type == type::file;

    } else if constexpr (std::is_same_v<T, object_ref>) {
      return m_type == type::object;

    } else /*if constexpr (std::is_convertible_v<T, std::string>)*/ {
      return m_type == type::string;
    }
  }

  /**
   * @brief Indicates whether or not the property holds a value equal to the
   * specified value.
   *
   * @tparam T the type of the value. An unsupported type will cause a
   * compile-time error. If `T` is convertible to `std::string`, e.g. `const
   * char*`, the behaviour of this function is as if `T` was `std::string`.
   *
   * @param value the value that will be compared with the stored value.
   *
   * @return `true` if the stored value is equal to the supplied value; `false`
   * otherwise.
   *
   * @since 0.2.0
   */
  template <typename T,
            typename = std::enable_if_t<detail::valid_property_type<T>()>>
  [[nodiscard]] auto is(const T& value) const -> bool
  {
    if constexpr (std::is_convertible_v<T, std::string>) {
      if (is<std::string>()) {
        return get<std::string>() == value;
      }
    } else {
      if (is<T>()) {
        return get<T>() == value;
      }
    }
    return false;
  }

  /**
   * @brief Returns the name associated with the property.
   *
   * @return the name associated with the property.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return m_name;
  }

  /**
   * @brief Returns the type associated with the property.
   *
   * @return the type associated with the property.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_type() const noexcept -> type
  {
    return m_type;
  }

 private:
  type m_type{type::string};
  std::string m_name;
  std::variant<std::string, file, object_ref, color, int, float, bool> m_value;
};

NLOHMANN_JSON_SERIALIZE_ENUM(property::type,
                             {{property::type::string, "string"},
                              {property::type::integer, "int"},
                              {property::type::floating, "float"},
                              {property::type::boolean, "bool"},
                              {property::type::color, "color"},
                              {property::type::object, "object"},
                              {property::type::file, "file"}})

}  // namespace step

#endif  // STEP_PROPERTY_HEADER

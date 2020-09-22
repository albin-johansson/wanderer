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

/**
 * @file step_object.hpp
 *
 * @brief Provides `object`, `polygon`, `polyline` and `template_object`.
 *
 * @author Albin Johansson
 *
 * @date 2020
 *
 * @copyright MIT License
 */

#ifndef STEP_OBJECT_HEADER
#define STEP_OBJECT_HEADER

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

#include "step_api.hpp"
#include "step_point.hpp"
#include "step_properties.hpp"
#include "step_text.hpp"
#include "step_types.hpp"

namespace step {

/**
 * @struct polygon
 *
 * @brief A simple data container for polygon objects.
 *
 * @since 0.1.0
 *
 * @headerfile step_object.hpp
 */
struct polygon final {
  std::vector<point> points;
};

/**
 * @struct polyline
 *
 * @brief A simple data container for polyline objects.
 *
 * @since 0.1.0
 *
 * @headerfile step_object.hpp
 */
struct polyline final {
  std::vector<point> points;
};

/**
 * @struct template_object
 *
 * @brief A simple data container for template objects.
 *
 * @since 0.1.0
 *
 * @headerfile step_object.hpp
 */
struct template_object final {
  std::string templateFile;
  // TODO std::shared_ptr<Tileset>
  // TODO std::shared_ptr<Object>
};

/**
 * @class object
 *
 * @brief Represents different kinds of objects in tile maps, such as polygons
 * or text.
 *
 * @since 0.1.0
 *
 * @headerfile step_object.hpp
 */
class object final {
 private:
  template <typename T>
  static constexpr auto valid_object_type() noexcept -> bool;

 public:
  /**
   * @brief Creates an tiled object from a JSON object.
   *
   * @param json the JSON object that represents the tiled object.
   *
   * @since 0.1.0
   */
  explicit object(const json& json)
      : m_id{json.at("id").get<int>()},
        m_x{json.at("x").get<double>()},
        m_y{json.at("y").get<double>()},
        m_width{json.at("width").get<double>()},
        m_height{json.at("height").get<double>()},
        m_rotation{json.at("rotation").get<double>()},
        m_name{json.at("name").get<std::string>()},
        m_type{json.at("type").get<std::string>()},
        m_isEllipse{detail::safe_get<bool>(json, "ellipse", false)},
        m_isPoint{detail::safe_get<bool>(json, "point", false)},
        m_visible{json.at("visible").get<bool>()}
  {
    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties.emplace(it.value());
    }

    if (const auto gidIt = json.find("gid"); gidIt != json.end()) {
      m_specificData.emplace<global_id>(gidIt->get<unsigned>());

    } else if (const auto textIt = json.find("text"); textIt != json.end()) {
      m_specificData.emplace<text>(*textIt);

    } else if (const auto polyIt = json.find("polygon"); polyIt != json.end()) {
      auto& poly = m_specificData.emplace<polygon>();

      for (const auto& [key, value] : polyIt->items()) {
        poly.points.emplace_back(point{value});
      }

    } else if (const auto lineIt = json.find("polyline");
               lineIt != json.end()) {
      auto& line = m_specificData.emplace<polyline>();

      for (const auto& [key, value] : lineIt->items()) {
        line.points.emplace_back(point{value});
      }

    } else if (json.contains("template")) {
      auto& templ = m_specificData.emplace<template_object>();
      json.at("template").get_to(templ.templateFile);
    }
  }

  /**
   * @brief Returns the incremental ID associated with the object.
   *
   * @return the incremental ID associated with the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto id() const noexcept -> int
  {
    return m_id;
  }

  /**
   * @brief Returns the x-coordinate of the object.
   *
   * @return the x-coordinate of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto x() const noexcept -> double
  {
    return m_x;
  }

  /**
   * @brief Returns the y-coordinate of the object.
   *
   * @return the y-coordinate of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto y() const noexcept -> double
  {
    return m_y;
  }

  /**
   * @brief Returns the width of the object.
   *
   * @return the width of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> double
  {
    return m_width;
  }

  /**
   * @brief Returns the height of the object.
   *
   * @return the height of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> double
  {
    return m_height;
  }

  /**
   * @brief Returns the amount of clockwise rotation of the object.
   *
   * @return the clockwise rotation of the object, in degrees.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto rotation() const noexcept -> double
  {
    return m_rotation;
  }

  /**
   * @brief Returns the name of the object.
   *
   * @return the name of the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string_view
  {
    return m_name;
  }

  /**
   * @brief Returns the type associated with the object.
   *
   * @return the type associated with the object.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto type() const -> std::string_view
  {
    return m_type;
  }

  /**
   * @brief Returns the properties associated with the object.
   *
   * @return the properties associated with the object; `nullptr` if there are
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const -> const properties*
  {
    return m_properties ? m_properties.operator->() : nullptr;
  }

  /**
   * @brief Indicates whether or not the object is visible.
   *
   * @return `true` if the object is visible; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto visible() const noexcept -> bool
  {
    return m_visible;
  }

  /**
   * Indicates whether or not the object represents an ellipse.
   *
   * @return `true` if the object represents an ellipse; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto is_ellipse() const noexcept -> bool
  {
    return m_isEllipse;
  }

  /**
   * @brief Indicates whether or not the object represents a point.
   *
   * @return `true` if the object represents a point; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto is_point() const noexcept -> bool
  {
    return m_isPoint;
  }

  /**
   * @brief Returns a reference to the internal object type-specific data.
   *
   * @note This function throws if the stored data isn't actually of the
   * specified type.
   *
   * @tparam T the type of the data to obtain, i.e. `polygon`, `polyline`,
   * `template_object`, `text` or `global_id`.
   *
   * @return a reference to the internal data.
   *
   * @since 0.2.0
   */
  template <typename T, typename = std::enable_if_t<valid_object_type<T>()>>
  [[nodiscard]] auto as() const -> const T&
  {
    return std::get<T>(m_specificData);
  }

  /**
   * @brief Returns a pointer to the internal object type-specific data.
   *
   * @note Unlike `get`, this function doesn't throw if the types mismatch,
   * instead `nullptr` is returned.
   *
   * @tparam T the type of the data to obtain, i.e. `polygon`, `polyline`,
   * `template_object`, `text` or `global_id`.
   *
   * @return a pointer to the internal data; `nullptr` if the types mismatch.
   *
   * @since 0.2.0
   */
  template <typename T, typename = std::enable_if_t<valid_object_type<T>()>>
  [[nodiscard]] auto try_as() const noexcept -> const T*
  {
    return std::get_if<T>(m_specificData);
  }

  /**
   * @brief Indicates whether or not the stored data is of the specified type.
   *
   * @tparam T the type to look for, i.e. `polygon`, `polyline`,
   * `template_object`, `text` or `global_id`.
   *
   * @return `true` if the stored data is of the specified type; `false`
   * otherwise.
   *
   * @since 0.2.0
   */
  template <typename T, typename = std::enable_if_t<valid_object_type<T>()>>
  [[nodiscard]] auto has() const noexcept -> bool
  {
    return std::holds_alternative<T>(m_specificData);
  }

 private:
  using data = std::variant<std::monostate,
                            polygon,
                            polyline,
                            text,
                            template_object,
                            global_id>;
  int m_id{0};
  double m_x{0};
  double m_y{0};
  double m_width{0};
  double m_height{0};
  double m_rotation{0};
  std::string m_name;
  std::string m_type;
  std::optional<properties> m_properties;
  data m_specificData;
  bool m_isEllipse{false};
  bool m_isPoint{false};
  bool m_visible{true};

  // TODO improve template object support
};

template <typename T>
constexpr auto object::valid_object_type() noexcept -> bool
{
  return std::is_same_v<T, polygon> || std::is_same_v<T, polyline> ||
         std::is_same_v<T, text> || std::is_same_v<T, template_object> ||
         std::is_same_v<T, global_id>;
}

}  // namespace step

#endif  // STEP_OBJECT_HEADER

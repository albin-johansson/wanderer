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
#include <string>
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
struct polygon {
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
struct polyline {
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
struct template_object {
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
  STEP_API
  explicit object(const json& json);

  /**
   * @brief Returns the incremental ID associated with the object.
   *
   * @return the incremental ID associated with the object.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto id() const noexcept -> int;

  /**
   * @brief Returns the x-coordinate of the object.
   *
   * @return the x-coordinate of the object.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto x() const noexcept -> double;

  /**
   * @brief Returns the y-coordinate of the object.
   *
   * @return the y-coordinate of the object.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto y() const noexcept -> double;

  /**
   * @brief Returns the width of the object.
   *
   * @return the width of the object.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto width() const noexcept -> double;

  /**
   * @brief Returns the height of the object.
   *
   * @return the height of the object.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto height() const noexcept -> double;

  /**
   * @brief Returns the amount of clockwise rotation of the object.
   *
   * @return the clockwise rotation of the object, in degrees.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto rotation() const noexcept -> double;

  /**
   * @brief Returns the name of the object.
   *
   * @return the name of the object.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto name() const -> std::string;

  /**
   * @brief Returns the type associated with the object.
   *
   * @return the type associated with the object.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto type() const -> std::string;

  /**
   * @brief Returns the properties associated with the object.
   *
   * @return the properties associated with the object; `nullptr` if there are
   * none.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto get_properties() const noexcept -> const properties*;

  /**
   * @brief Indicates whether or not the object is visible.
   *
   * @return `true` if the object is visible; `false` otherwise.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto visible() const noexcept -> bool;

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
  [[nodiscard]] auto get() const -> const T&
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
  [[nodiscard]] auto try_get() const noexcept -> const T*
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

  /**
   * Indicates whether or not the object represents an ellipse.
   *
   * @return `true` if the object represents an ellipse; `false` otherwise.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto is_ellipse() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the object represents a point.
   *
   * @return `true` if the object represents a point; `false` otherwise.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto is_point() const noexcept -> bool;

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
  std::unique_ptr<properties> m_properties;
  data m_specificData;
  bool m_ellipse{false};
  bool m_point{false};
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

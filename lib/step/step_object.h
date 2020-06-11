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

#ifndef STEP_OBJECT_HEADER
#define STEP_OBJECT_HEADER

#include <string>
#include <variant>
#include <vector>

#include "step_api.h"
#include "step_point.h"
#include "step_properties.h"
#include "step_text.h"
#include "step_types.h"

namespace step {

/**
 * A simple data container for polygon objects.
 *
 * @since 0.1.0
 */
struct Polygon {
  std::vector<Point> points;
};

/**
 * A simple data container for polyline objects.
 *
 * @since 0.1.0
 */
struct Polyline {
  std::vector<Point> points;
};

/**
 * A simple data container for template objects.
 *
 * @since 0.1.0
 */
struct Template {
  std::string templateFile;
  // TODO std::shared_ptr<Tileset>
  // TODO std::shared_ptr<Object>
};

/**
 * The Object class represents different kinds of objects in tile maps, such
 * as polygons or text.
 *
 * @since 0.1.0
 */
class Object final {
 public:
  STEP_API friend void from_json(const JSON&, Object&);

  /**
   * Returns the incremental ID associated with the object.
   *
   * @return the incremental ID associated with the object.
   * @since 0.1.0
   */
  STEP_QUERY int id() const noexcept;

  /**
   * Returns the x-coordinate of the object.
   *
   * @return the x-coordinate of the object.
   * @since 0.1.0
   */
  STEP_QUERY double x() const noexcept;

  /**
   * Returns the y-coordinate of the object.
   *
   * @return the y-coordinate of the object.
   * @since 0.1.0
   */
  STEP_QUERY double y() const noexcept;

  /**
   * Returns the width of the object.
   *
   * @return the width of the object.
   * @since 0.1.0
   */
  STEP_QUERY double width() const noexcept;

  /**
   * Returns the height of the object.
   *
   * @return the height of the object.
   * @since 0.1.0
   */
  STEP_QUERY double height() const noexcept;

  /**
   * Returns the amount of clockwise rotation of the object.
   *
   * @return the clockwise rotation of the object, in degrees.
   * @since 0.1.0
   */
  STEP_QUERY double rotation() const noexcept;

  /**
   * Returns the name of the object.
   *
   * @return the name of the object.
   * @since 0.1.0
   */
  STEP_QUERY std::string name() const;

  /**
   * Returns the type associated with the object.
   *
   * @return the type associated with the object.
   * @since 0.1.0
   */
  STEP_QUERY std::string type() const;

  /**
   * Returns the properties associated with the object.
   *
   * @return the properties associated with the object.
   * @since 0.1.0
   */
  STEP_QUERY const Properties& properties() const noexcept;

  /**
   * Returns the polygon associated with the object.
   *
   * @return the polygon associated with the object; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Polygon> polygon() const noexcept;

  /**
   * Returns the polyline associated with the object.
   *
   * @return the polyline associated with the object; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Polyline> polyline() const noexcept;

  /**
   * Returns the tile GID associated with the object.
   *
   * @return the tile GID associated with the object; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<GID> tile_gid() const noexcept;

  /**
   * Returns the template data associated with the object.
   *
   * @return the template data associated with the object; nothing if there is
   * none.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Template> template_data() const;

  /**
   * Returns the text associated with the object.
   *
   * @return the text associated with the object; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Text> text() const;

  /**
   * Indicates whether or not the object is visible.
   *
   * @return true if the object is visible; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool visible() const noexcept;

  /**
   * Indicates whether or not the object represents an ellipse.
   *
   * @return true if the object represents an ellipse; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_ellipse() const noexcept;

  /**
   * Indicates whether or not the object represents a point.
   *
   * @return true if the object represents a point; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_point() const noexcept;

  /**
   * Indicates whether or not the object represents a polygon.
   *
   * @return true if the object represents a polygon; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_polygon() const noexcept;

  /**
   * Indicates whether or not the object represents a polyline.
   *
   * @return true if the object represents a polyline; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_polyline() const noexcept;

  /**
   * Indicates whether or not the object represents a text object.
   *
   * @return true if the object represents a text object; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_text() const noexcept;

  /**
   * Indicates whether or not the object represents an object template.
   *
   * @return true if the object represents an object template; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_template() const noexcept;

  /**
   * Indicates whether or not the object represents a tile.
   *
   * @return true if the object represents a tile; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_tile() const noexcept;

 private:
  int m_id{0};
  double m_x{0};
  double m_y{0};
  double m_width{0};
  double m_height{0};
  double m_rotation{0};
  std::string m_name;
  std::string m_type;
  Properties m_properties;
  std::variant<std::monostate, Polygon, Polyline, Text, Template, GID>
      m_specificData;
  bool m_ellipse{false};
  bool m_point{false};
  bool m_visible{true};

  // TODO improve template object support
};

STEP_API void from_json(const JSON& json, Object& object);

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_object.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_OBJECT_HEADER

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

#ifndef STEP_LAYER_HEADER
#define STEP_LAYER_HEADER

#include <string>
#include <variant>
#include <vector>

#include "step_api.h"
#include "step_group.h"
#include "step_image_layer.h"
#include "step_object_group.h"
#include "step_properties.h"
#include "step_tile_layer.h"
#include "step_types.h"

namespace step {

/**
 * The Layer class represents the tile layers that reside in the tile maps.
 *
 * @since 0.1.0
 */
class Layer final {
 public:
  /**
   * The Type enum class provides identifiers for all of the different
   * possible layer types.
   *
   * @since 0.1.0
   */
  enum class Type { TileLayer, ObjectGroup, ImageLayer, Group };

  STEP_API friend void from_json(const JSON&, Layer&);

  /**
   * Indicates whether or not the layer is a tile layer.
   *
   * @return true if the layer is a tile layer; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_tile_layer() const noexcept;

  /**
   * Indicates whether or not the layer is an image layer.
   *
   * @return true if the layer is an image layer; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_image_layer() const noexcept;

  /**
   * Indicates whether or not the layer is an object group.
   *
   * @return true if the layer is an object group; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_object_group() const noexcept;

  /**
   * Indicates whether or not the layer is a group.
   *
   * @return true if the layer is a group; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool is_group() const noexcept;

  /**
   * Returns the type of the layer.
   *
   * @return the type of the layer.
   * @since 0.1.0
   */
  STEP_QUERY Type type() const noexcept;

  /**
   * Returns the unique integer ID associated with the layer.
   *
   * @return the unique integer ID associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY int id() const noexcept;

  /**
   * Returns the tile layer information associated with the layer. This
   * method will throw an exception if the layer isn't a tile layer.
   *
   * @return the tile layer information associated with the layer.
   * @throws StepException if the layer isn't actually a tile layer.
   * @since 0.1.0
   */
  STEP_QUERY const TileLayer& as_tile_layer() const;

  /**
   * Returns the image layer information associated with the layer. This
   * method will throw an exception if the layer isn't an image layer.
   *
   * @return the image layer information associated with the layer.
   * @throws StepException if the layer isn't actually an image layer.
   * @since 0.1.0
   */
  STEP_QUERY const ImageLayer& as_image_layer() const;

  /**
   * Returns the object group information associated with the layer. This
   * method will throw an exception if the layer isn't an object group.
   *
   * @return the object group information associated with the layer.
   * @throws StepException if the layer isn't actually an object group.
   * @since 0.1.0
   */
  STEP_QUERY const ObjectGroup& as_object_group() const;

  /**
   * Returns the group information associated with the layer. This
   * method will throw an exception if the layer isn't a group.
   *
   * @return the group information associated with the layer.
   * @throws StepException if the layer isn't actually a group.
   * @since 0.1.0
   */
  STEP_QUERY const Group& as_group() const;

  /**
   * Returns the amount of columns in the layer.
   *
   * @return the amount of columns in the layer.
   * @since 0.1.0
   */
  STEP_QUERY int width() const noexcept;

  /**
   * Returns the amount of rows in the layer.
   *
   * @return the amount of rows in the layer.
   * @since 0.1.0
   */
  STEP_QUERY int height() const noexcept;

  /**
   * Returns the properties associated with the layer.
   *
   * @return the properties associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY const Properties& properties() const noexcept;

  /**
   * Returns the x-coordinate of where the layer content begins. This is used by
   * infinite maps.
   *
   * @return the x-coordinate of where the layer content begins.
   * @since 0.1.0
   */
  STEP_QUERY int start_x() const noexcept;

  /**
   * Returns the y-coordinate of where the layer content begins. This is used by
   * infinite maps.
   *
   * @return the y-coordinate of where the layer content begins.
   * @since 0.1.0
   */
  STEP_QUERY int start_y() const noexcept;

  /**
   * Returns the horizontal offset of the layer. The default value of
   * this property is 0.
   *
   * @return the horizontal offset of the layer, in pixels.
   * @since 0.1.0
   */
  STEP_QUERY double offset_x() const noexcept;

  /**
   * Returns the vertical offset of the layer. The default value of
   * this property is 0.
   *
   * @return the vertical offset of the layer, in pixels.
   * @since 0.1.0
   */
  STEP_QUERY double offset_y() const noexcept;

  /**
   * Returns the opacity of the layer.
   *
   * @return the opacity of the layer, in the range [0, 1].
   * @since 0.1.0
   */
  STEP_QUERY double opacity() const noexcept;

  /**
   * Returns the name associated with the layer.
   *
   * @return the name associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY std::string name() const;

  /**
   * Indicates whether or not the layer is visible.
   *
   * @return true if the layer is visible; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool visible() const noexcept;

 private:
  Type m_type;
  int m_id{0};
  std::variant<TileLayer, ImageLayer, ObjectGroup, Group> m_layerData;
  Properties m_properties;
  int m_width{0};
  int m_height{0};
  int m_startX{0};
  int m_startY{0};
  double m_offsetX{0};
  double m_offsetY{0};
  double m_opacity{1};
  std::string m_name;
  bool m_visible{true};

  void init_common(const JSON& json);
};

STEP_API void from_json(const JSON& json, Layer& layer);

STEP_SERIALIZE_ENUM(Layer::Type,
                    {{Layer::Type::TileLayer, "tilelayer"},
                     {Layer::Type::ImageLayer, "imagelayer"},
                     {Layer::Type::ObjectGroup, "objectgroup"},
                     {Layer::Type::Group, "group"}})

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_layer.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_LAYER_HEADER

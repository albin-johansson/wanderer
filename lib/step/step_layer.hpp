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

#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "step_api.hpp"
#include "step_group.hpp"
#include "step_image_layer.hpp"
#include "step_object_group.hpp"
#include "step_properties.hpp"
#include "step_tile_layer.hpp"
#include "step_types.hpp"

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

  STEP_API
  explicit Layer(const json& json);

  /**
   * Indicates whether or not the layer is a tile layer.
   *
   * @return true if the layer is a tile layer; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY
  auto is_tile_layer() const noexcept -> bool;

  /**
   * Indicates whether or not the layer is an image layer.
   *
   * @return true if the layer is an image layer; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY
  auto is_image_layer() const noexcept -> bool;

  /**
   * Indicates whether or not the layer is an object group.
   *
   * @return true if the layer is an object group; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY
  auto is_object_group() const noexcept -> bool;

  /**
   * Indicates whether or not the layer is a group.
   *
   * @return true if the layer is a group; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY
  auto is_group() const noexcept -> bool;

  /**
   * Returns the type of the layer.
   *
   * @return the type of the layer.
   * @since 0.1.0
   */
  STEP_QUERY
  auto type() const noexcept -> Type;

  /**
   * Returns the unique integer ID associated with the layer.
   *
   * @return the unique integer ID associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY
  auto id() const noexcept -> int;

  /**
   * Returns the tile layer information associated with the layer. This
   * method will throw an exception if the layer isn't a tile layer.
   *
   * @return the tile layer information associated with the layer.
   * @throws step_exception if the layer isn't actually a tile layer.
   * @since 0.1.0
   */
  STEP_QUERY
  auto as_tile_layer() const -> const TileLayer&;

  /**
   * Returns the image layer information associated with the layer. This
   * method will throw an exception if the layer isn't an image layer.
   *
   * @return the image layer information associated with the layer.
   * @throws step_exception if the layer isn't actually an image layer.
   * @since 0.1.0
   */
  STEP_QUERY
  auto as_image_layer() const -> const ImageLayer&;

  /**
   * Returns the object group information associated with the layer. This
   * method will throw an exception if the layer isn't an object group.
   *
   * @return the object group information associated with the layer.
   * @throws step_exception if the layer isn't actually an object group.
   * @since 0.1.0
   */
  STEP_QUERY
  auto as_object_group() const -> const ObjectGroup&;

  /**
   * Returns the group information associated with the layer. This
   * method will throw an exception if the layer isn't a group.
   *
   * @return the group information associated with the layer.
   * @throws step_exception if the layer isn't actually a group.
   * @since 0.1.0
   */
  STEP_QUERY
  auto as_group() const -> const Group&;

  /**
   * Returns the amount of columns in the layer.
   *
   * @return the amount of columns in the layer.
   * @since 0.1.0
   */
  STEP_QUERY
  auto width() const noexcept -> int;

  /**
   * Returns the amount of rows in the layer.
   *
   * @return the amount of rows in the layer.
   * @since 0.1.0
   */
  STEP_QUERY
  auto height() const noexcept -> int;

  /**
   * Returns the properties associated with the layer.
   *
   * @return the properties associated with the layer; null if there are none.
   * @since 0.1.0
   */
  STEP_QUERY
  auto get_properties() const noexcept -> const properties*;

  /**
   * Returns the x-coordinate of where the layer content begins. This is used by
   * infinite maps.
   *
   * @return the x-coordinate of where the layer content begins.
   * @since 0.1.0
   */
  STEP_QUERY
  auto start_x() const noexcept -> int;

  /**
   * Returns the y-coordinate of where the layer content begins. This is used by
   * infinite maps.
   *
   * @return the y-coordinate of where the layer content begins.
   * @since 0.1.0
   */
  STEP_QUERY
  auto start_y() const noexcept -> int;

  /**
   * Returns the horizontal offset of the layer. The default value of
   * this property is 0.
   *
   * @return the horizontal offset of the layer, in pixels.
   * @since 0.1.0
   */
  STEP_QUERY
  auto offset_x() const noexcept -> double;

  /**
   * Returns the vertical offset of the layer. The default value of
   * this property is 0.
   *
   * @return the vertical offset of the layer, in pixels.
   * @since 0.1.0
   */
  STEP_QUERY
  auto offset_y() const noexcept -> double;

  /**
   * Returns the opacity of the layer.
   *
   * @return the opacity of the layer, in the range [0, 1].
   * @since 0.1.0
   */
  STEP_QUERY
  auto opacity() const noexcept -> double;

  /**
   * Returns the name associated with the layer.
   *
   * @return the name associated with the layer.
   * @since 0.1.0
   */
  STEP_QUERY
  auto name() const -> std::string;

  /**
   * Indicates whether or not the layer is visible.
   *
   * @return true if the layer is visible; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY
  auto visible() const noexcept -> bool;

 private:
  Type m_type;
  int m_id{0};
  std::variant<std::monostate, TileLayer, ImageLayer, ObjectGroup, Group>
      m_layerData;
  std::unique_ptr<properties> m_properties;
  int m_width{0};
  int m_height{0};
  int m_startX{0};
  int m_startY{0};
  double m_offsetX{0};
  double m_offsetY{0};
  double m_opacity{1};
  std::string m_name;
  bool m_visible{true};

  void init_common(const json& json);
};

NLOHMANN_JSON_SERIALIZE_ENUM(Layer::Type,
                             {{Layer::Type::TileLayer, "tilelayer"},
                              {Layer::Type::ImageLayer, "imagelayer"},
                              {Layer::Type::ObjectGroup, "objectgroup"},
                              {Layer::Type::Group, "group"}})

}  // namespace step

#endif  // STEP_LAYER_HEADER

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

#ifndef STEP_TILED_MAP_HEADER
#define STEP_TILED_MAP_HEADER

#include <string>
#include <string_view>
#include <vector>

#include "step_api.h"
#include "step_color.h"
#include "step_layer.h"
#include "step_properties.h"
#include "step_tileset.h"
#include "step_types.h"

namespace step {

/**
 * The Map class represents tile map files created in the Tiled editor.
 *
 * @since 0.1.0
 */
class Map final {
 public:
  enum class RenderOrder { RightDown, RightUp, LeftDown, LeftUp };
  enum class Orientation { Orthogonal, Isometric, Staggered, Hexagonal };
  enum class StaggerAxis { X, Y };
  enum class StaggerIndex { Odd, Even };

  /**
   * @param root the file path of the directory that contains the map.
   * @param file the name of the JSON map file, including the .json extension.
   * @since 0.1.0
   */
  STEP_API Map(std::string_view root, std::string_view file);

  /**
   * Returns the width of the map.
   *
   * @return the width of the map.
   * @since 0.1.0
   */
  STEP_QUERY int width() const noexcept;

  /**
   * Returns the height of the map.
   *
   * @return the height of the map.
   * @since 0.1.0
   */
  STEP_QUERY int height() const noexcept;

  /**
   * Returns the width of the tiles in the map.
   *
   * @return the width of the tiles in the map.
   * @since 0.1.0
   */
  STEP_QUERY int tile_width() const noexcept;

  /**
   * Returns the height of the tiles in the map.
   *
   * @return the height of the tiles in the map.
   * @since 0.1.0
   */
  STEP_QUERY int tile_height() const noexcept;

  /**
   * Returns the next layer ID, this is incremented every time an layer is
   * added to the map in the Tiled editor.
   *
   * @return the next layer ID.
   * @since 0.1.0
   */
  STEP_QUERY int next_layer_id() const noexcept;

  /**
   * Returns the next object ID, this is incremented every time an object is
   * placed in the map in the Tiled editor.
   *
   * @return the next object ID.
   * @since 0.1.0
   */
  STEP_QUERY int next_object_id() const noexcept;

  /**
   * Returns the tile layers associated with the map.
   *
   * @return the tile layers associated with the map.
   * @since 0.1.0
   */
  STEP_QUERY const std::vector<Layer>& layers() const noexcept;

  /**
   * Returns the tilesets associated with the map.
   *
   * @return the tilesets associated with the map.
   * @since 0.1.0
   */
  STEP_QUERY const std::vector<Tileset>& tilesets() const noexcept;

  /**
   * Returns the properties associated with the map.
   *
   * @return the properties associated with the map.
   * @since 0.1.0
   */
  STEP_QUERY const Properties& properties() const noexcept;

  /**
   * Returns the orientation of the map.
   *
   * @return the orientation of the map.
   * @since 0.1.0
   */
  STEP_QUERY Orientation orientation() const noexcept;

  /**
   * Returns the render-order associated with the map. The default value of
   * this property is <code>RightDown</code>. This property is only used by
   * orthogonal maps.
   *
   * @return the render-order associated with the map.
   * @since 0.1.0
   */
  STEP_QUERY RenderOrder render_order() const noexcept;

  /**
   * Returns the stagger axis associated with the map. This property is only
   * for staggered and hexagonal maps.
   *
   * @return the stagger axis associated with the map.
   * @since 0.1.0
   */
  STEP_QUERY StaggerAxis stagger_axis() const noexcept;

  /**
   * Returns the stagger index associated with the map. This property is only
   * for staggered and hexagonal maps.
   *
   * @return the stagger index associated with the map.
   * @since 0.1.0
   */
  STEP_QUERY StaggerIndex stagger_index() const noexcept;

  /**
   * Indicates whether or not the map is infinite.
   *
   * @return true if the map is infinite; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool infinite() const noexcept;

  /**
   * Returns the length of the side of a hex tile, in pixels. This property
   * is only for hexagonal maps.
   *
   * @return the length of the side of a hex tile, in pixels.
   * @since 0.1.0
   */
  STEP_QUERY int hex_side_length() const noexcept;

  /**
   * Returns the background color associated with the map. This property is
   * optional.
   *
   * @return the background color of the map.
   * @since 0.1.0
   */
  STEP_QUERY Maybe<Color> background_color() const noexcept;

  /**
   * Returns the JSON format version associated with the map.
   *
   * @return the JSON format version associated with the map.
   * @since 0.1.0
   */
  STEP_QUERY double json_version() const noexcept;

  /**
   * Returns the Tiled version associated with the map.
   *
   * @return the Tiled version associated with the map.
   * @since 0.1.0
   */
  STEP_QUERY std::string tiled_version() const;

 private:
  int m_width{0};
  int m_height{0};
  int m_tileWidth{0};
  int m_tileHeight{0};
  int m_nextLayerID{0};
  int m_nextObjectID{0};
  std::vector<Layer> m_layers;
  std::vector<Tileset> m_tilesets;
  Properties m_properties;
  Orientation m_orientation{Orientation::Orthogonal};
  RenderOrder m_renderOrder{RenderOrder::RightDown};
  StaggerAxis m_staggerAxis{StaggerAxis::X};
  StaggerIndex m_staggerIndex{StaggerIndex::Odd};
  int m_hexSideLength{0};
  Maybe<Color> m_backgroundColor;
  std::string m_tiledVersion;
  double m_jsonVersion{0};
  bool m_infinite{false};

  void parse(std::string_view root, const JSON& json);
};

STEP_SERIALIZE_ENUM(Map::RenderOrder,
                    {{Map::RenderOrder::RightDown, "right-down"},
                     {Map::RenderOrder::RightUp, "right-up"},
                     {Map::RenderOrder::LeftDown, "left-down"},
                     {Map::RenderOrder::LeftUp, "left-up"}})

STEP_SERIALIZE_ENUM(Map::Orientation,
                    {{Map::Orientation::Orthogonal, "orthogonal"},
                     {Map::Orientation::Isometric, "isometric"},
                     {Map::Orientation::Staggered, "staggered"},
                     {Map::Orientation::Hexagonal, "hexagonal"}})

STEP_SERIALIZE_ENUM(Map::StaggerAxis,
                    {{Map::StaggerAxis::X, "x"}, {Map::StaggerAxis::Y, "y"}})

STEP_SERIALIZE_ENUM(Map::StaggerIndex,
                    {{Map::StaggerIndex::Odd, "odd"},
                     {Map::StaggerIndex::Even, "even"}})

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_map.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_TILED_MAP_HEADER

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

#ifndef STEP_TILESET_HEADER
#define STEP_TILESET_HEADER

#include <memory>
#include <string_view>
#include <vector>

#include "step_api.hpp"
#include "step_color.hpp"
#include "step_grid.hpp"
#include "step_properties.hpp"
#include "step_terrain.hpp"
#include "step_tile.hpp"
#include "step_tile_offset.hpp"
#include "step_types.hpp"
#include "step_wang_set.hpp"

namespace step {

class Tileset;

/**
 * The Tileset class represents a collection of tiles associated with an
 * image. All tilesets have a global ID (GID) associated with them, that
 * starts at 1 for the first tileset.
 *
 * @since 0.1.0
 */
class Tileset final {
 public:
  STEP_API
  static Tileset embedded(const json& json);

  STEP_API
  static Tileset external(std::string_view root,
                          global_id id,
                          std::string_view src);

  /**
   * Returns the GID (Global ID) of the first tile in the tileset.
   *
   * @return the GID (Global ID) of the first tile in the tileset.
   * @since 0.1.0
   */
  STEP_QUERY
  global_id first_gid() const noexcept;

  /**
   * Returns the maximum width of tiles in the tileset.
   *
   * @return the maximum width of tiles in the tileset.
   * @since 0.1.0
   */
  STEP_QUERY
  int tile_width() const noexcept;

  /**
   * Returns the maximum height of tiles in the tileset.
   *
   * @return the maximum height of tiles in the tileset.
   * @since 0.1.0
   */
  STEP_QUERY
  int tile_height() const noexcept;

  /**
   * Returns the number of tiles in the tileset.
   *
   * @return the number of tiles in the tileset.
   * @since 0.1.0
   */
  STEP_QUERY
  int tile_count() const noexcept;

  /**
   * Returns the number of columns in the tileset.
   *
   * @return the number of columns in the tileset.
   * @since 0.1.0
   */
  STEP_QUERY
  int columns() const noexcept;

  /**
   * Returns the width of the source image in pixels.
   *
   * @return the width of the source image in pixels.
   * @since 0.1.0
   */
  STEP_QUERY
  int image_width() const noexcept;

  /**
   * Returns the height of the source image in pixels.
   *
   * @return the height of the source image in pixels.
   * @since 0.1.0
   */
  STEP_QUERY
  int image_height() const noexcept;

  /**
   * Returns the buffer amount between the image edge and the first tile, in
   * pixels.
   *
   * @return the buffer amount between the image edge and the first tile, in
   * pixels.
   * @since 0.1.0
   */
  STEP_QUERY
  int margin() const noexcept;

  /**
   * Returns the amount of spacing between adjacent tiles in the tileset, in
   * pixels.
   *
   * @return the amount of spacing between adjacent tiles in the tileset, in
   * pixels.
   * @since 0.1.0
   */
  STEP_QUERY
  int spacing() const noexcept;

  /**
   * Returns the tiles associated with the tileset that have custom
   * properties. This property is optional.
   *
   * @return the tiles associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY const std::vector<tile>& tiles() const noexcept;

  /**
   * Returns all of the Wang sets that are associated with the tileset.
   *
   * @return the Wang sets associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY const std::vector<WangSet>& wang_sets() const;

  /**
   * Returns the properties associated with the tileset.
   *
   * @return the properties associated with the tileset; null if there are none.
   * @since 0.1.0
   */
  STEP_QUERY const properties* get_properties() const noexcept;

  /**
   * Returns the terrains associated with the tileset. This property is
   * optional.
   *
   * @return the terrains associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY const std::vector<Terrain>& terrains() const noexcept;

  /**
   * Returns the path to the external file that holds the actual tileset
   * data, if this tileset isn't embedded. This method will return the empty
   * string if the tileset is embedded.
   *
   * @return the path to the external file that holds the tileset data if the
   * the tileset is external; the empty string is returned if the tileset is
   * embedded.
   * @since 0.1.0
   */
  STEP_QUERY std::string source() const;

  /**
   * Returns the path to the image associated with the tileset.
   *
   * @return the path to the image associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY std::string image() const;

  /**
   * Returns the name associated with the tileset.
   *
   * @return the name associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY std::string name() const;

  /**
   * Returns the background color of the tileset. This property is optional.
   *
   * @return the background color of the tileset; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY std::optional<color> background_color() const noexcept;

  /**
   * Returns the transparent color of the tileset. This property is optional.
   *
   * @return the transparent color of the tileset; nothing if there is none.
   * @since 0.1.0
   */
  STEP_QUERY std::optional<color> transparent_color() const noexcept;

  /**
   * Returns the grid associated with the tileset. This property is optional.
   *
   * @return the grid associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY std::optional<Grid> grid() const noexcept;

  /**
   * Returns the tile offset associated with the tileset. This property is
   * optional.
   *
   * @return the tile offset associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY std::optional<TileOffset> tile_offset() const noexcept;

  /**
   * Returns the Tiled version associated with the tileset.
   *
   * @return the Tiled version associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY std::string tiled_version() const;

  /**
   * Returns the JSON format version associated with the tileset.
   *
   * @return the JSON format version associated with the tileset.
   * @since 0.1.0
   */
  STEP_QUERY double json_version() const noexcept;

 private:
  global_id m_firstGID{1};
  int m_tileWidth = 0;
  int m_tileHeight = 0;
  int m_tileCount = 0;
  int m_nColumns = 0;
  int m_imageWidth = 0;
  int m_imageHeight = 0;
  int m_margin = 0;
  int m_spacing = 0;
  std::vector<tile> m_tiles;
  std::vector<Terrain> m_terrains;
  std::vector<WangSet> m_wangSets;
  std::unique_ptr<properties> m_properties;
  std::string m_image;
  std::string m_source;
  std::string m_name;
  std::optional<color> m_backgroundColor;
  std::optional<color> m_transparentColor;
  std::optional<Grid> m_grid;
  std::optional<TileOffset> m_tileOffset;

  std::string m_tiledVersion;
  double m_jsonVersion = 0;

  Tileset(std::string_view root, global_id id, std::string_view src);

  explicit Tileset(const json& json);

  void parse(const json& json);
};

}  // namespace step

#endif  // STEP_TILESET_HEADER

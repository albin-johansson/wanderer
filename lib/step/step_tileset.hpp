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

#include <memory>       // unique_ptr
#include <optional>     // optional
#include <string_view>  // string_view
#include <vector>       // vector

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

class tileset;

/**
 * @class tileset
 *
 * @brief Represents a collection of tiles associated with an image.
 *
 * @details All tilesets have a global ID (GID) associated with them, that
 * starts at 1 for the first tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_tileset.hpp
 */
class tileset final {
 public:
  [[nodiscard]] static auto embedded(const json& json)
      -> std::unique_ptr<tileset>
  {
    return std::unique_ptr<tileset>{new tileset{json}};
  }

  [[nodiscard]] static auto external(std::string_view root,
                                     global_id id,
                                     std::string_view src)
      -> std::unique_ptr<tileset>
  {
    return std::unique_ptr<tileset>{new tileset{root, id, src}};
  }

  /**
   * @brief Returns the GID (Global ID) of the first tile in the tileset.
   *
   * @return the GID (Global ID) of the first tile in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto first_gid() const noexcept -> global_id
  {
    return m_firstGID;
  }

  /**
   * @brief Returns the maximum width of tiles in the tileset.
   *
   * @return the maximum width of tiles in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_width() const noexcept -> int
  {
    return m_tileWidth;
  }

  /**
   * @brief Returns the maximum height of tiles in the tileset.
   *
   * @return the maximum height of tiles in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_height() const noexcept -> int
  {
    return m_tileHeight;
  }

  /**
   * @brief Returns the number of tiles in the tileset.
   *
   * @return the number of tiles in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_count() const noexcept -> int
  {
    return m_tileCount;
  }

  /**
   * @brief Returns the number of columns in the tileset.
   *
   * @return the number of columns in the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto columns() const noexcept -> int
  {
    return m_nColumns;
  }

  /**
   * @brief Returns the width of the source image in pixels.
   *
   * @return the width of the source image in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image_width() const noexcept -> int
  {
    return m_imageWidth;
  }

  /**
   * @brief Returns the height of the source image in pixels.
   *
   * @return the height of the source image in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image_height() const noexcept -> int
  {
    return m_imageHeight;
  }

  /**
   * @brief Returns the buffer amount between the image edge and the first tile,
   * in pixels.
   *
   * @return the buffer amount between the image edge and the first tile, in
   * pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto margin() const noexcept -> int
  {
    return m_margin;
  }

  /**
   * @brief Returns the amount of spacing between adjacent tiles in the tileset,
   * in pixels.
   *
   * @return the amount of spacing between adjacent tiles in the tileset, in
   * pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto spacing() const noexcept -> int
  {
    return m_spacing;
  }

  /**
   * @brief Returns the tiles associated with the tileset that have custom
   * properties.
   *
   * @details This property is optional.
   *
   * @return the tiles associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tiles() const -> const std::vector<tile>&
  {
    return m_tiles;
  }

  /**
   * @brief Returns all of the Wang sets that are associated with the tileset.
   *
   * @return the Wang sets associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto wang_sets() const -> const std::vector<wang_set>&
  {
    return m_wangSets;
  }

  /**
   * @brief Returns the properties associated with the tileset.
   *
   * @return the properties associated with the tileset; null if there are none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const noexcept -> const properties*
  {
    return m_properties.get();
  }

  /**
   * @brief Returns the terrains associated with the tileset.
   *
   * @details This property is optional.
   *
   * @return the terrains associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto terrains() const -> const std::vector<terrain>&
  {
    return m_terrains;
  }

  /**
   * @brief Returns the path to the external file that holds the actual tileset
   * data, if this tileset isn't embedded.
   *
   * @details This method will return the empty string if the tileset is
   * embedded.
   *
   * @return the path to the external file that holds the tileset data if the
   * the tileset is external; the empty string is returned if the tileset is
   * embedded.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto source() const -> std::string_view
  {
    return m_source;
  }

  /**
   * @brief Returns the path to the image associated with the tileset.
   *
   * @return the path to the image associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image() const -> std::string_view
  {
    return m_image;
  }

  /**
   * @brief Returns the name associated with the tileset.
   *
   * @return the name associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string_view
  {
    return m_name;
  }

  /**
   * @brief Returns the background color of the tileset.
   *
   * @details This property is optional.
   *
   * @return the background color of the tileset; `std::nullopt` if there is
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto background_color() const noexcept
      -> const std::optional<color>&
  {
    return m_backgroundColor;
  }

  /**
   * @brief Returns the transparent color of the tileset. This property is
   * optional.
   *
   * @return the transparent color of the tileset; `std::nullopt`if there is
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto transparent_color() const noexcept
      -> const std::optional<color>&
  {
    return m_transparentColor;
  }

  /**
   * @brief Returns the grid associated with the tileset. This property is
   * optional.
   *
   * @return the grid associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_grid() const noexcept -> const std::optional<grid>&
  {
    return m_grid;
  }

  /**
   * @brief Returns the tile offset associated with the tileset.
   *
   * @details This property is optional.
   *
   * @return the tile offset associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_tile_offset() const noexcept
      -> const std::optional<tile_offset>&
  {
    return m_tileOffset;
  }

  /**
   * @brief Returns the Tiled version associated with the tileset.
   *
   * @return the Tiled version associated with the tileset.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tiled_version() const -> std::string_view
  {
    return m_tiledVersion;
  }

  /**
   * Returns the JSON format version associated with the tileset.
   *
   * @return the JSON format version associated with the tileset.
   * @since 0.1.0
   */
  [[nodiscard]] auto json_version() const noexcept -> double
  {
    return m_jsonVersion;
  }

 private:
  global_id m_firstGID{1};
  int m_tileWidth{};
  int m_tileHeight{};
  int m_tileCount{};
  int m_nColumns{};
  int m_imageWidth{};
  int m_imageHeight{};
  int m_margin{};
  int m_spacing{};
  std::vector<tile> m_tiles;
  std::vector<terrain> m_terrains;
  std::vector<wang_set> m_wangSets;
  std::unique_ptr<properties> m_properties;
  std::string m_image;
  std::string m_source;
  std::string m_name;
  std::optional<color> m_backgroundColor;
  std::optional<color> m_transparentColor;
  std::optional<grid> m_grid;
  std::optional<tile_offset> m_tileOffset;
  std::string m_tiledVersion;
  double m_jsonVersion{};

  tileset(std::string_view root, global_id id, std::string_view src)
      : m_firstGID{id},
        m_source{src.data()}
  {
    std::string fullPath{root.data()};
    fullPath += src.data();
    parse(detail::parse_json(fullPath));
  }

  explicit tileset(const json& json)
  {
    parse(json);
  }

  void parse(const json& json)
  {
    if (json.at("type").get<std::string>() != "tileset") {
      throw step_exception{R"(Tileset "type" must be "tileset"!)"};
    }

    json.at("tilewidth").get_to(m_tileWidth);
    json.at("tileheight").get_to(m_tileHeight);
    json.at("tilecount").get_to(m_tileCount);
    json.at("columns").get_to(m_nColumns);
    json.at("imagewidth").get_to(m_imageWidth);
    json.at("imageheight").get_to(m_imageHeight);
    json.at("margin").get_to(m_margin);
    json.at("spacing").get_to(m_spacing);
    json.at("image").get_to(m_image);
    json.at("name").get_to(m_name);

    if (const auto it = json.find("firstgid"); it != json.end()) {
      m_firstGID = global_id{it->get<unsigned>()};
    }

    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties = std::make_unique<properties>(*it);
    }

    detail::safe_bind(json, "tiledversion", m_tiledVersion);
    detail::safe_bind(json, "version", m_jsonVersion);
    detail::bind_opt(json, "grid", m_grid);
    detail::emplace_opt(json, "tileoffset", m_tileOffset);

    const auto fill_if_array = [&json](auto& container, std::string_view key) {
      const auto it = json.find(key);
      if (it != json.end() && it->is_array()) {
        container.reserve(it->size());
        for (const auto& [key, value] : it->items()) {
          container.emplace_back(value);
        }
      }
    };

    fill_if_array(m_tiles, "tiles");
    fill_if_array(m_terrains, "terrains");
    fill_if_array(m_wangSets, "wangsets");

    if (const auto it = json.find("backgroundcolor"); it != json.end()) {
      m_backgroundColor = color{it->get<std::string>()};
    }

    if (const auto it = json.find("transparentcolor"); it != json.end()) {
      m_transparentColor = color{it->get<std::string>()};
    }
  }
};

}  // namespace step

#endif  // STEP_TILESET_HEADER

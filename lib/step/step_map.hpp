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

#ifndef STEP_MAP_HEADER
#define STEP_MAP_HEADER

#include <memory>       // unique_ptr
#include <string>       // string
#include <string_view>  // string_view
#include <vector>       // vector

#include "step_api.hpp"
#include "step_color.hpp"
#include "step_layer.hpp"
#include "step_properties.hpp"
#include "step_tileset.hpp"
#include "step_types.hpp"

namespace step {

/**
 * @class map
 *
 * @brief Represents tile map files created in the Tiled editor.
 *
 * @since 0.1.0
 *
 * @headerfile step_map.hpp
 */
class map final {
 public:
  enum class render_order { right_down, right_up, left_down, left_up };

  enum class orientation { orthogonal, isometric, staggered, hexagonal };

  enum class stagger_axis { x, y };

  enum class stagger_index { odd, even };

  explicit map(const fs::path& path)
  {
    auto parent = path.parent_path();
    parent += fs::path::preferred_separator;

    parse(parent.string(), detail::parse_json(path.string()));
  }

  /**
   * @param root the file path of the directory that contains the map.
   * @param file the name of the JSON map file, including the .json extension.
   *
   * @since 0.1.0
   */
  [[deprecated("Use the path version instead!")]] map(std::string_view root,
                                                      std::string_view file)
  {
    std::string map{root.data()};
    map += file;
    parse(root, detail::parse_json(map));
  }

  /**
   * @brief Returns the width of the map.
   *
   * @return the width of the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_width;
  }

  /**
   * @brief Returns the height of the map.
   *
   * @return the height of the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_height;
  }

  /**
   * @brief Returns the width of the tiles in the map.
   *
   * @return the width of the tiles in the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_width() const noexcept -> int
  {
    return m_tileWidth;
  }

  /**
   * @brief Returns the height of the tiles in the map.
   *
   * @return the height of the tiles in the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_height() const noexcept -> int
  {
    return m_tileHeight;
  }

  /**
   * @brief Returns the next layer ID, this is incremented every time an layer
   * is added to the map in the Tiled editor.
   *
   * @return the next layer ID.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto next_layer_id() const noexcept -> int
  {
    return m_nextLayerID;
  }

  /**
   * @brief Returns the next object ID, this is incremented every time an object
   * is placed in the map in the Tiled editor.
   *
   * @return the next object ID.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto next_object_id() const noexcept -> int
  {
    return m_nextObjectID;
  }

  /**
   * @brief Returns the tile layers associated with the map.
   *
   * @return the tile layers associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto layers() const -> const std::vector<layer>&
  {
    return m_layers;
  }

  /**
   * @brief Returns the tilesets associated with the map.
   *
   * @return the tilesets associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tilesets() const
      -> const std::vector<std::unique_ptr<tileset>>&
  {
    return m_tilesets;
  }

  /**
   * @brief Returns the properties associated with the map.
   *
   * @return the properties associated with the map; null if there are none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const noexcept -> const properties*
  {
    return m_properties.get();
  }

  /**
   * @brief Returns the orientation of the map.
   *
   * @return the orientation of the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_orientation() const noexcept -> orientation
  {
    return m_orientation;
  }

  /**
   * @brief Returns the render-order associated with the map.
   *
   * @details The default value of this property is `right_down`.
   *
   * @note This property is only used by orthogonal maps.
   *
   * @return the render-order associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_render_order() const noexcept -> render_order
  {
    return m_renderOrder;
  }

  /**
   * @brief Returns the stagger axis associated with the map.
   *
   * @details This property is only for staggered and hexagonal maps.
   *
   * @return the stagger axis associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_stagger_axis() const noexcept -> stagger_axis
  {
    return m_staggerAxis;
  }

  /**
   * @brief Returns the stagger index associated with the map.
   *
   * @details This property is only for staggered and hexagonal maps.
   *
   * @return the stagger index associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_stagger_index() const noexcept -> stagger_index
  {
    return m_staggerIndex;
  }

  /**
   * @brief Indicates whether or not the map is infinite.
   *
   * @return true if the map is infinite; false otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto infinite() const noexcept -> bool
  {
    return m_infinite;
  }

  /**
   * @brief Returns the length of the side of a hex tile, in pixels.
   *
   * @details This property is only for hexagonal maps.
   *
   * @return the length of the side of a hex tile, in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto hex_side_length() const noexcept -> int
  {
    return m_hexSideLength;
  }

  /**
   * @brief Returns the background color associated with the map.
   *
   * @details This property is optional.
   *
   * @return the background color of the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto background_color() const noexcept
      -> const std::optional<color>&
  {
    return m_backgroundColor;
  }

  /**
   * @brief Returns the JSON format version associated with the map.
   *
   * @return the JSON format version associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto json_version() const noexcept -> double
  {
    return m_jsonVersion;
  }

  /**
   * @brief Returns the Tiled version associated with the map.
   *
   * @return the Tiled version associated with the map.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tiled_version() const -> std::string_view
  {
    return m_tiledVersion;
  }

 private:
  int m_width{0};
  int m_height{0};
  int m_tileWidth{0};
  int m_tileHeight{0};
  int m_nextLayerID{0};
  int m_nextObjectID{0};
  std::vector<layer> m_layers;
  std::vector<std::unique_ptr<tileset>> m_tilesets;
  std::unique_ptr<properties> m_properties;
  orientation m_orientation{orientation::orthogonal};
  render_order m_renderOrder{render_order::right_down};
  stagger_axis m_staggerAxis{stagger_axis::x};
  stagger_index m_staggerIndex{stagger_index::odd};
  int m_hexSideLength{0};
  std::optional<color> m_backgroundColor;
  std::string m_tiledVersion;
  double m_jsonVersion{0};
  bool m_infinite{false};

  void parse(std::string_view root, const json& json)
  {
    using namespace std::string_view_literals;
    if (const auto it = json.find("type");
        it == json.end() || it.key() == "map"sv) {
      throw step_exception{R"(Map "type" attribute must be "map"!)"};
    }

    json.at("width").get_to(m_width);
    json.at("height").get_to(m_height);
    json.at("tilewidth").get_to(m_tileWidth);
    json.at("tileheight").get_to(m_tileHeight);
    json.at("infinite").get_to(m_infinite);
    json.at("nextlayerid").get_to(m_nextLayerID);
    json.at("nextobjectid").get_to(m_nextObjectID);
    json.at("orientation").get_to(m_orientation);
    json.at("version").get_to(m_jsonVersion);
    json.at("tiledversion").get_to(m_tiledVersion);

    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties = std::make_unique<properties>(*it);
    }

    detail::safe_bind(json, "renderorder", m_renderOrder);
    detail::safe_bind(json, "staggeraxis", m_staggerAxis);
    detail::safe_bind(json, "staggerindex", m_staggerIndex);
    detail::safe_bind(json, "hexsidelength", m_hexSideLength);

    if (const auto it = json.find("backgroundcolor"); it != json.end()) {
      m_backgroundColor = color{it->get<std::string>()};
    }

    for (const auto& [key, value] : json.at("layers").items()) {
      m_layers.emplace_back(value);
    }

    for (const auto& [key, value] : json.at("tilesets").items()) {
      if (const auto it = value.find("source"); it != value.end()) {
        const auto firstgid = global_id{value.at("firstgid").get<unsigned>()};
        const auto src = it->get<std::string>();
        m_tilesets.push_back(tileset::external(root, firstgid, src.data()));
      } else {
        m_tilesets.push_back(tileset::embedded(value));
      }
    }
  }
};

NLOHMANN_JSON_SERIALIZE_ENUM(map::render_order,
                             {{map::render_order::right_down, "right-down"},
                              {map::render_order::right_up, "right-up"},
                              {map::render_order::left_down, "left-down"},
                              {map::render_order::left_up, "left-up"}})

NLOHMANN_JSON_SERIALIZE_ENUM(map::orientation,
                             {{map::orientation::orthogonal, "orthogonal"},
                              {map::orientation::isometric, "isometric"},
                              {map::orientation::staggered, "staggered"},
                              {map::orientation::hexagonal, "hexagonal"}})

NLOHMANN_JSON_SERIALIZE_ENUM(map::stagger_axis,
                             {{map::stagger_axis::x, "x"},
                              {map::stagger_axis::y, "y"}})

NLOHMANN_JSON_SERIALIZE_ENUM(map::stagger_index,
                             {{map::stagger_index::odd, "odd"},
                              {map::stagger_index::even, "even"}})

}  // namespace step

#endif  // STEP_MAP_HEADER

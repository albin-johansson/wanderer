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
 * @file step_tile.hpp
 *
 * @brief Provides the `tile` class.
 *
 * @author Albin Johansson
 *
 * @date 2020
 *
 * @copyright MIT License
 */

#ifndef STEP_TILE_HEADER
#define STEP_TILE_HEADER

#include <array>     // array
#include <optional>  // optional
#include <string>    // string

#include "step_animation.hpp"
#include "step_api.hpp"
#include "step_fwd.hpp"
#include "step_layer.hpp"
#include "step_properties.hpp"
#include "step_types.hpp"
#include "step_utils.hpp"

namespace step {

/**
 * @class tile
 *
 * @brief Provides information about a tile in a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_tile.hpp
 */
class tile final {
 public:
  /**
   * @enum terrain_pos
   *
   * @brief Provides values that represent the different positions that could be
   * inhabited by terrain IDs, in relation to the tile.
   *
   * @since 0.1.0
   *
   * @headerfile step_tile.hpp
   */
  enum class terrain_pos {
    top_left = 0,
    top_right = 1,
    bottom_left = 2,
    bottom_right = 3
  };

  explicit tile(const json& json) : m_id{json.at("id").get<int>()}
  {
    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties.emplace(*it);
    }

    if (const auto it = json.find("terrain"); it != json.end()) {
      m_terrain.emplace();
      for (const auto& [key, value] : it->items()) {
        m_terrain->at(detail::convert<std::size_t>(key)) = value.get<int>();
      }
    }

    if (const auto it = json.find("objectgroup"); it != json.end()) {
      m_objectGroup.emplace(*it);
    }

    detail::emplace_opt(json, "animation", m_animation);

    detail::bind_opt(json, "type", m_type);
    detail::bind_opt(json, "image", m_image);
    detail::bind_opt(json, "imagewidth", m_imageWidth);
    detail::bind_opt(json, "imageheight", m_imageHeight);
    detail::bind_opt(json, "probability", m_probability);
  }

  /**
   * @brief Returns the local ID associated with the tile.
   *
   * @return the local ID associated with the tile.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto id() const noexcept -> local_id
  {
    return m_id;
  }

  /**
   * @brief Returns the animation associated with the tile.
   *
   * @return the animation associated with the tile; `std::nullopt` if there is
   * no animation associated with the tile.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_animation() const noexcept
      -> const std::optional<animation>&
  {
    return m_animation;
  }

  /**
   * @brief Returns the properties associated with the tile.
   *
   * @note Don't take ownership of the returned pointer.
   *
   * @return the properties associated with the tile; `nullptr` if there are
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const -> const properties*
  {
    return m_properties ? m_properties.operator->() : nullptr;
  }

  /**
   * @brief Returns the object group layer associated with the tile.
   *
   * @note Don't take ownership of the returned pointer.
   *
   * @return a shared pointer to the object group associated with the tile;
   * `nullptr` if there is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto object_group() const noexcept -> const layer*
  {
    return m_objectGroup ? m_objectGroup.operator->() : nullptr;
  }

  /**
   * @brief Returns the type of the tile.
   *
   * @return the type of the tile; `std::nullopt` if there is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto type() const -> const std::optional<std::string>&
  {
    return m_type;
  }

  /**
   * @brief Returns the image associated with the tile.
   *
   * @return the image associated with the tile; `std::nullopt` if there is
   * none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image() const -> const std::optional<std::string>&
  {
    return m_image;
  }

  /**
   * @brief Returns the width of the image associated with the tile.
   *
   * @return the width of the image associated with the tile; `std::nullopt` if
   * there is no image associated with the tile.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image_width() const noexcept -> std::optional<int>
  {
    return m_imageWidth;
  }

  /**
   * @brief Returns the height of the image associated with the tile.
   *
   * @return the height of the image associated with the tile; `std::nullopt` if
   * there is no image associated with the tile.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto image_height() const noexcept -> std::optional<int>
  {
    return m_imageHeight;
  }

  /**
   * @brief Returns the probability associated with the tile.
   *
   * @return the probability associated with the tile; `std::nullopt` if there
   * is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto probability() const noexcept -> std::optional<double>
  {
    return m_probability;
  }

  /**
   * @brief Returns the ID of the terrain at the specified position, in relation
   * to the tile.
   *
   * @param position the position that will be checked.
   *
   * @return the ID of the terrain at the specified position; `std::nullopt`
   * if there is none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto terrain_at(terrain_pos position) const noexcept
      -> std::optional<int>
  {
    if (m_terrain) {
      return m_terrain->at(static_cast<std::size_t>(position));
    } else {
      return std::nullopt;
    }
  }

 private:
  local_id m_id{0};
  std::optional<properties> m_properties;
  std::optional<layer> m_objectGroup;
  std::optional<animation> m_animation;
  std::optional<std::array<int, 4>> m_terrain;
  std::optional<std::string> m_type;
  std::optional<std::string> m_image;
  std::optional<int> m_imageWidth;
  std::optional<int> m_imageHeight;
  std::optional<double> m_probability;
};

}  // namespace step

#endif  // STEP_TILE_HEADER

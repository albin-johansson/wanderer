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

#include <memory>
#include <vector>

#include "step_animation.hpp"
#include "step_api.hpp"
#include "step_fwd.hpp"
#include "step_layer.hpp"
#include "step_types.hpp"

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

  STEP_API
  explicit tile(const json& json);

  /**
   * @brief Returns the local ID associated with the tile.
   *
   * @return the local ID associated with the tile.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto id() const noexcept -> local_id;

  /**
   * @brief Returns the animation associated with the tile.
   *
   * @return the animation associated with the tile; `std::nullopt` if there is
   * no animation associated with the tile.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto get_animation() const noexcept -> std::optional<animation>;

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
  STEP_QUERY
  auto get_properties() const -> const properties*;

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
  STEP_QUERY
  auto object_group() const noexcept -> const Layer*;

  /**
   * @brief Returns the type of the tile.
   *
   * @return the type of the tile; `std::nullopt` if there is none.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto type() const -> std::optional<std::string>;

  /**
   * @brief Returns the image associated with the tile.
   *
   * @return the image associated with the tile; `std::nullopt` if there is
   * none.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto image() const -> std::optional<std::string>;

  /**
   * @brief Returns the width of the image associated with the tile.
   *
   * @return the width of the image associated with the tile; `std::nullopt` if
   * there is no image associated with the tile.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto image_width() const noexcept -> std::optional<int>;

  /**
   * @brief Returns the height of the image associated with the tile.
   *
   * @return the height of the image associated with the tile; `std::nullopt` if
   * there is no image associated with the tile.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto image_height() const noexcept -> std::optional<int>;

  /**
   * @brief Returns the probability associated with the tile.
   *
   * @return the probability associated with the tile; `std::nullopt` if there
   * is none.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto probability() const noexcept -> std::optional<double>;

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
  STEP_QUERY
  auto terrain_at(terrain_pos position) const noexcept -> std::optional<int>;

 private:
  local_id m_id{0};

  std::unique_ptr<properties> m_properties;
  std::unique_ptr<Layer> m_objectGroup;

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

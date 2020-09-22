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

#ifndef STEP_TERRAIN_HEADER
#define STEP_TERRAIN_HEADER

#include <memory>
#include <string>
#include <vector>

#include "step_api.hpp"
#include "step_properties.hpp"
#include "step_utils.hpp"

namespace step {

/**
 * @class terrain
 *
 * @brief Represents optional terrains in a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_terrain.hpp
 */
class terrain final {
 public:
  explicit terrain(const json& json)
      : m_tile{json.at("tile").get<int>()},
        m_name{json.at("name").get<std::string>()}
  {
    if (const auto it = json.find("properties"); it != json.end()) {
      m_properties = std::make_unique<properties>(*it);
    }
  }

  /**
   * @brief Returns the local GID of the tile associated with the terrain.
   *
   * @return the local GID of the tile associated with the terrain.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile() const noexcept -> local_id
  {
    return m_tile;
  }

  /**
   * @brief Returns the name associated with the terrain.
   *
   * @return the name associated with the terrain.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return m_name;
  }

  /**
   * @brief Returns the properties associated with the terrain.
   *
   * @details This property is optional.
   *
   * @return the properties associated with the terrain; null if there are none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const noexcept -> const properties*
  {
    return m_properties.get();
  }

 private:
  local_id m_tile{0};
  std::string m_name;
  std::unique_ptr<properties> m_properties;
};

}  // namespace step

#endif  // STEP_TERRAIN_HEADER

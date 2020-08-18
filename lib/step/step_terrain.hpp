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

namespace step {

/**
 * The Terrain class represents optional terrains in a tileset.
 *
 * @since 0.1.0
 */
class Terrain final {
 public:
  STEP_API
  explicit Terrain(const json& json);

  /**
   * Returns the local GID of the tile associated with the terrain.
   *
   * @return the local GID of the tile associated with the terrain.
   * @since 0.1.0
   */
  STEP_QUERY
  auto tile() const noexcept -> local_id;

  /**
   * Returns the name associated with the terrain.
   *
   * @return the name associated with the terrain.
   * @since 0.1.0
   */
  STEP_QUERY
  auto name() const -> std::string;

  /**
   * Returns the properties associated with the terrain. This property is
   * optional.
   *
   * @return the properties associated with the terrain; null if there are none.
   * @since 0.1.0
   */
  STEP_QUERY
  auto get_properties() const noexcept -> const properties*;

 private:
  local_id m_tile{0};
  std::string m_name;
  std::unique_ptr<properties> m_properties;
};

}  // namespace step

#endif  // STEP_TERRAIN_HEADER

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

#include <string>
#include <vector>

#include "step_api.h"
#include "step_properties.h"

namespace step {

/**
 * The Terrain class represents optional terrains in a tileset.
 *
 * @since 0.1.0
 */
class Terrain final {
 public:
  STEP_API friend void from_json(const JSON&, Terrain&);

  /**
   * Returns the local GID of the tile associated with the terrain.
   *
   * @return the local GID of the tile associated with the terrain.
   * @since 0.1.0
   */
  [[nodiscard]] int tile() const noexcept { return m_tile; }

  /**
   * Returns the name associated with the terrain.
   *
   * @return the name associated with the terrain.
   * @since 0.1.0
   */
  [[nodiscard]] std::string name() const { return m_name; }

  /**
   * Returns the properties associated with the terrain. This property is
   * optional.
   *
   * @return the properties associated with the terrain.
   * @since 0.1.0
   */
  [[nodiscard]] const Properties& properties() const noexcept
  {
    return m_properties;
  }

 private:
  int m_tile;
  std::string m_name;
  Properties m_properties;
};

void from_json(const JSON& json, Terrain& terrain);

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_terrain.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_TERRAIN_HEADER

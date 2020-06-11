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

#ifndef STEP_CHUNK_HEADER
#define STEP_CHUNK_HEADER

#include "step_api.h"
#include "step_data.h"
#include "step_types.h"

namespace step {

/**
 * The Chunk class represents so called chunks, that store the tile layer
 * data for infinite maps.
 *
 * @since 0.1.0
 */
class Chunk final {
 public:
  STEP_API friend void from_json(const JSON&, Chunk&);

  /**
   * Returns the x-coordinate of the chunk.
   *
   * @return the x-coordinate of the chunk.
   * @since 0.1.0
   */
  STEP_QUERY int x() const noexcept;

  /**
   * Returns the y-coordinate of the chunk.
   *
   * @return the y-coordinate of the chunk.
   * @since 0.1.0
   */
  STEP_QUERY int y() const noexcept;

  /**
   * Returns the width of the chunk.
   *
   * @return the width of the chunk.
   * @since 0.1.0
   */
  STEP_QUERY int width() const noexcept;

  /**
   * Returns the height of the chunk.
   *
   * @return the height of the chunk.
   * @since 0.1.0
   */
  STEP_QUERY int height() const noexcept;

  /**
   * Returns the data associated with the chunk.
   *
   * @return the data associated with the chunk.
   * @since 0.1.0
   */
  STEP_QUERY const detail::Data& data() const noexcept;

 private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;
  detail::Data m_data;
};

STEP_API void from_json(const JSON& json, Chunk& chunk);

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_chunk.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_CHUNK_HEADER

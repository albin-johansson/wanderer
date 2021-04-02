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

#ifndef STEP_FRAME_HEADER
#define STEP_FRAME_HEADER

#include "step_api.hpp"
#include "step_types.hpp"

namespace step {

/**
 * The Frame class represents a frame in an animation.
 *
 * @since 0.1.0
 */
class Frame final {
 public:
  explicit Frame(const json& json)
      : m_tileID{json.at("tileid").get<int>()},
        m_duration{json.at("duration").get<int>()}
  {}

  /**
   * Returns the local tile ID that is associated with the frame.
   *
   * @return the local tile ID that is associated with the frame.
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_id() const noexcept -> local_id
  {
    return m_tileID;
  }

  /**
   * Returns the duration of this frame, in milliseconds.
   *
   * @return the duration of this frame, in milliseconds.
   * @since 0.1.0
   */
  [[nodiscard]] auto duration() const noexcept -> int
  {
    return m_duration;
  }

 private:
  local_id m_tileID{0};
  int m_duration{0};
};

}  // namespace step

#endif  // STEP_FRAME_HEADER
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

/*
 * @file step_animation.hpp
 *
 * @brief Provides the `animation` class.
 *
 * @author Albin Johansson
 *
 * @date 2020
 *
 * @copyright MIT License
 */

#ifndef STEP_ANIMATION_HEADER
#define STEP_ANIMATION_HEADER

#include <vector>

#include "step_api.hpp"
#include "step_frame.hpp"
#include "step_types.hpp"

namespace step {

/**
 * @class animation
 *
 * @brief Represents a collection of frames, used to animate tiles.
 *
 * @since 0.1.0
 *
 * @todo Add begin() and end(), maybe even at() & operator[].
 *
 * @headerfile step_animation.hpp
 */
class animation final {
 public:
  STEP_API
  explicit animation(const json& json);

  /**
   * @brief Returns the frames associated with the animation.
   *
   * @return the frames associated with the animation.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto frames() const -> const std::vector<Frame>&;

  /**
   * @brief Returns the amount of frames that constitute the animation.
   *
   * @return the amount of frames that constitute the animation.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto num_frames() const noexcept -> int;

 private:
  std::vector<Frame> m_frames;
};

}  // namespace step

#endif  // STEP_ANIMATION_HEADER

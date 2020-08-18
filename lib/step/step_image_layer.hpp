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

#ifndef STEP_IMAGE_LAYER_HEADER
#define STEP_IMAGE_LAYER_HEADER

#include <string>

#include "step_api.hpp"
#include "step_color.hpp"
#include "step_types.hpp"

namespace step {

/**
 * The ImageLayer class represents the API for layers that represent "image
 * layers", that is layers that are represented by an image.
 *
 * @since 0.1.0
 */
class ImageLayer final {
 public:
  STEP_API
  friend void from_json(const json&, ImageLayer&);

  /**
   * Returns the image used by the image layer.
   *
   * @return the image associated with the image layer.
   * @since 0.1.0
   */
  STEP_QUERY
  std::string image() const;

  /**
   * Returns the transparent color used by the image layer. This property is
   * optional.
   *
   * @return the transparent color used by the image layer; nothing if there is
   * none.
   * @since 0.1.0
   */
  STEP_QUERY
  std::optional<color> transparent_color() const noexcept;

 private:
  std::string m_image;
  std::optional<color> m_transparentColor;
};

STEP_API
void from_json(const json& json, ImageLayer& layer);

}  // namespace step

#endif  // STEP_IMAGE_LAYER_HEADER

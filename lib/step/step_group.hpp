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

#ifndef STEP_GROUP_HEADER
#define STEP_GROUP_HEADER

#include <memory>
#include <vector>

#include "step_api.hpp"
#include "step_types.hpp"

namespace step {

class Layer;

/**
 * The Group class represents the API for layers that represent "groups", that
 * in turn contain zero or more layers.
 *
 * @since 0.1.0
 */
class Group final {
 public:
  STEP_API
  friend void from_json(const json&, Group&);

  /**
   * Iterates over all of the layers store in this group.
   *
   * @tparam Lambda the type of the lambda object.
   * @param lambda the lambda that takes one argument, <code>const
   * Layer&</code>.
   * @since 0.1.0
   */
  template <typename Lambda>
  void each(Lambda&& lambda) const
  {
    for (const auto& layer : m_layers) {
      lambda(*layer);
    }
  }

  /**
   * Returns the layer at the specified index. This method will throw an
   * exception if the index is out-of-bounds.
   *
   * @param index the index of the desired layer.
   * @return the layer at the specified index.
   * @since 0.1.0
   */
  STEP_QUERY
  const Layer& at(int index) const;

  /**
   * Returns the amount of layers that are in the group.
   *
   * @return the amount of layers that are in the group.
   * @since 0.1.0
   */
  STEP_QUERY
  int layers() const noexcept;

 private:
  std::vector<std::unique_ptr<Layer>> m_layers;
};

STEP_API
void from_json(const json& json, Group& group);

}  // namespace step

#endif  // STEP_GROUP_HEADER

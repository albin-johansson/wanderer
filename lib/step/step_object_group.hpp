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

#ifndef STEP_OBJECT_GROUP_HEADER
#define STEP_OBJECT_GROUP_HEADER

#include <vector>

#include "step_api.hpp"
#include "step_object.hpp"
#include "step_types.hpp"

namespace step {

/**
 * @class object_group
 *
 * @brief Represents the API for layers that represent "object groups", that
 * hold data about various objects in a tile map.
 *
 * @todo begin, end, remove objects-getter
 *
 * @since 0.1.0
 *
 * @headerfile step_object_group.hpp
 */
class object_group final {
 public:
  /**
   * @enum object_group::draw_order
   *
   * @brief Provides hints for how rendering should be performed of layers.
   *
   * @since 0.1.0
   */
  enum class draw_order { top_down, index };

  explicit object_group(const json& json) : m_drawOrder{json.at("draworder")}
  {
    m_objects.reserve(json.size());
    for (const auto& [key, value] : json.at("objects").items()) {
      m_objects.emplace_back(value);
    }
  }

  /**
   * @brief Returns the draw order used by the object group.
   *
   * @details The default value of this property is `top_down`.
   *
   * @return the draw order used by the object group.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_draw_order() const noexcept -> draw_order
  {
    return m_drawOrder;
  }

  /**
   * @brief Returns the objects contained in the object group.
   *
   * @return the objects contained in the object group.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto objects() const -> const std::vector<object>&
  {
    return m_objects;
  }

 private:
  draw_order m_drawOrder{draw_order::top_down};
  std::vector<object> m_objects;
};

NLOHMANN_JSON_SERIALIZE_ENUM(object_group::draw_order,
                             {{object_group::draw_order::index, "index"},
                              {object_group::draw_order::top_down, "topdown"}})

}  // namespace step

#endif  // STEP_OBJECT_GROUP_HEADER

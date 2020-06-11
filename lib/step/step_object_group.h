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

#include "step_api.h"
#include "step_object.h"
#include "step_types.h"

namespace step {

/**
 * The ObjectGroup class represents the API for layers that represent "object
 * groups", that hold data about various objects in a tilemap.
 *
 * @since 0.1.0
 */
class ObjectGroup final {
 public:
  /**
   * The DrawOrder enum class provides hints for how rendering should be
   * performed of layers.
   *
   * @since 0.1.0
   */
  enum class DrawOrder { TopDown, Index };

  STEP_API friend void from_json(const JSON&, ObjectGroup&);

  /**
   * Returns the draw order used by the object group. The default value of
   * this property is <code>TopDown</code>.
   *
   * @return the draw order used by the object group.
   * @since 0.1.0
   */
  STEP_QUERY DrawOrder draw_order() const noexcept;

  /**
   * Returns the objects contained in the object group.
   *
   * @return the objects contained in the object group.
   * @since 0.1.0
   */
  STEP_QUERY const std::vector<Object>& objects() const;

 private:
  DrawOrder m_drawOrder{DrawOrder::TopDown};
  std::vector<Object> m_objects;
};

STEP_API void from_json(const JSON& json, ObjectGroup& group);

STEP_SERIALIZE_ENUM(ObjectGroup::DrawOrder,
                    {{ObjectGroup::DrawOrder::Index, "index"},
                     {ObjectGroup::DrawOrder::TopDown, "topdown"}})

}  // namespace step

#endif  // STEP_OBJECT_GROUP_HEADER

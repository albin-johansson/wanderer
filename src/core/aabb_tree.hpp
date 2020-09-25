/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 James Randall
 * Copyright (c) 2019-2020 Albin Johansson: adapted and improved original
 * Simple Voxel Engine source code.
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

#pragma once

#include <algorithm>  // min, max
#include <entt.hpp>
#include <forward_list>  // forward_list
#include <map>           // map
#include <optional>      // optional
#include <vector>        // vector

#include "vector2.hpp"

namespace wanderer {

/**
 * @struct aabb
 *
 * @brief Represents an AABB (Axis-Aligned Bounding Box).
 *
 * @headerfile aabb_tree.hpp
 */
struct aabb final
{
  vector2f min{};  ///< The top-left corner position.
  vector2f max{};  ///< The bottom-right corner position.
  float area{};    ///< The area of the AABB.
};

/**
 * @struct aabb_node
 *
 * @brief Represents a node in an AABB tree.
 *
 * @details Contains an AABB and the entity associated with the AABB, along
 * with tree information.
 *
 * @headerfile aabb_tree.hpp
 */
struct aabb_node final
{
  aabb box;
  entt::entity entity{entt::null};
  std::optional<int> parent{};
  std::optional<int> left{};
  std::optional<int> right{};
  std::optional<int> next{};
};

/**
 * @brief Indicates whether or not the node is a leaf.
 *
 * @param node the node that will be checked.
 *
 * @return `true` if the node is a leaf; `false` otherwise.
 */
[[nodiscard]] inline auto is_leaf(const aabb_node& node) noexcept -> bool
{
  return !node.left;
}

/**
 * @brief Returns an AABB that is the union of two AABBs.
 *
 * @param fst the first AABB.
 * @param snd the second AABB.
 *
 * @return the union of the two AABBs.
 */
[[nodiscard]] inline auto merge(const aabb& fst, const aabb& snd) noexcept
    -> aabb
{
  aabb result;

  result.min.set_x(std::min(fst.min.x(), snd.min.x()));
  result.min.set_y(std::min(fst.min.y(), snd.min.y()));

  result.max.set_x(std::max(fst.max.x(), snd.max.x()));
  result.max.set_y(std::max(fst.max.y(), snd.max.y()));

  const auto width = result.max.x() - result.min.x();
  const auto height = result.max.y() - result.min.y();
  result.area = width * height;

  return result;
}

/**
 * @brief Returns an AABB based on the specified position and size.
 *
 * @param position the position of the AABB.
 * @param size the size of the AABB.
 *
 * @return the created AABB.
 */
[[nodiscard]] inline auto make_aabb(const vector2f& position,
                                    const vector2f& size) -> aabb
{
  aabb box;

  box.min = position;
  box.max = box.min + size;

  //  box.max.set_x(box.min.x() + size.x());
  //  box.max.set_y(box.min.y() + size.y());

  const auto width = box.max.x() - box.min.x();
  const auto height = box.max.y() - box.min.y();
  box.area = width * height;

  return box;
}

[[nodiscard]] inline auto contains(const aabb& source,
                                   const aabb& other) noexcept -> bool
{
  return other.min.x() >= source.min.x() && other.max.x() <= source.max.x() &&
         other.min.y() >= source.min.y() && other.max.y() <= source.max.y();
}

[[nodiscard]] inline auto overlaps(const aabb& fst, const aabb& snd) noexcept
    -> bool
{
  return (fst.max.x() > snd.min.x()) && (fst.min.x() < snd.max.x()) &&
         (fst.max.y() > snd.min.y()) && (fst.min.y() < snd.max.y());
}

/**
 * @class aabb_tree
 *
 * @brief Represents a tree of AABBs used for efficient collision detection.
 *
 * @details This class was adapted from James Randall's AABB system used in
 * his <a href="https://github.com/JamesRandall/SimpleVoxelEngine">Simple Voxel
 * Engine</a> project, which uses the MIT license. A helpful
 * article can be found <a
 * href="https://www.azurefromthetrenches.com/introductory-guide-to-aabb-tree-collision-detection/">here</a>.
 *
 * @headerfile aabb_tree.hpp
 */
class aabb_tree final
{
 public:
  aabb_tree();

  void insert_object(entt::entity id, const aabb& box);

  void remove_object(entt::entity id);

  void update_object(entt::entity id, const aabb& box);

  [[nodiscard]] auto query_overlaps(entt::entity id) const
      -> std::forward_list<entt::entity>;

  [[nodiscard]] auto get_aabb(entt::entity id) const -> const aabb&
  {
    return m_nodes.at(m_entities.at(id)).box;
  }

  [[nodiscard]] auto size() const noexcept -> int
  {
    return static_cast<int>(m_entities.size());
  }

 private:
  std::map<entt::entity, int> m_entities;
  std::vector<aabb_node> m_nodes;
  std::optional<int> m_rootIndex{};
  std::optional<int> m_nextFreeNodeIndex{};
  int m_allocatedNodes{};
  int m_nodeCapacity{24};
  int m_growthSize{m_nodeCapacity};

  void fix_upwards_tree(std::optional<int> nodeIndex);

  [[nodiscard]] auto allocate_node() -> int;

  void deallocate_node(int nodeIndex);

  [[nodiscard]] auto find_best_insertion_position(const aabb_node& leafNode)
      -> int;

  void insert_leaf(int leafIndex);

  void remove_leaf(int leafIndex);

  void update_leaf(int leafIndex, const aabb& box);
};

}  // namespace wanderer

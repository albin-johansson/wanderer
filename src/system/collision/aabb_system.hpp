/*
 * The implementation of this system was heavily inspired by James Randall's
 * AABB system used in his <a
 * href="https://github.com/JamesRandall/SimpleVoxelEngine">Simple Voxel
 * Engine</a> project. A helpful article can be found <a
 * href="https://www.azurefromthetrenches.com/introductory-guide-to-aabb-tree-collision-detection/">here</a>
 */

#pragma once

#include <area.hpp>
#include <entt.hpp>
#include <point.hpp>
#include <stack>  // stack

#include "component/aabb.hpp"
#include "vector2.hpp"

/**
 * @namespace wanderer::sys::aabb
 * @brief Provides the AABB system.
 */
namespace wanderer::sys::aabb {

[[nodiscard, deprecated]] inline auto is_leaf(
    const comp::aabb_node& node) noexcept -> bool
{
  return node.left == entt::null;
}

[[deprecated]] void validate(comp::aabb& aabb) noexcept;

//[[nodiscard]] inline auto move(const comp::aabb& aabb,
//                               const vector2f& position) noexcept ->
//                               comp::aabb
//{
//  comp::aabb moved = aabb;
//
//  moved.min = position;
//  moved.max = position + (aabb.max - aabb.min);
//
//  validate(moved);
//
//  return moved;
//}

/**
 * @brief Creates and returns an AABB instance.
 *
 * @details This is a convenience method that handles the calculation of the
 * center point and area of the created box.
 *
 * @param pos the position of the box.
 * @param size the size of the box.
 *
 * @return the created AABB instance.
 */
[[nodiscard, deprecated]] auto make_aabb(const cen::fpoint& pos,
                                         const cen::farea& size) noexcept
    -> comp::aabb;

/**
 * @brief Returns an AABB for the supplied boxes.
 *
 * @details Creates and returns an AABB that is sized to encapsulate both of
 * the supplied boxes.
 *
 * @param fst the first AABB.
 * @param snd the second AABB.
 *
 * @return an AABB that is the merged result of the two supplied boxes.
 */
[[nodiscard, deprecated]] auto merge(const comp::aabb& fst,
                                     const comp::aabb& snd) noexcept
    -> comp::aabb;

/**
 * @brief Indicates whether or not two AABBs overlap.
 *
 * @param fst the first box.
 * @param snd the second box.
 * @return `true` if the boxes overlap; `false` otherwise.
 */
[[nodiscard, deprecated]] auto overlaps(const comp::aabb& fst,
                                        const comp::aabb& snd) noexcept -> bool;

/**
 * @brief Indicates whether or not an AABB contains another AABB.
 *
 * @param source the box that will be checked to see if it contains the other
 * box.
 * @param other the box that will be looked for in the source box.
 *
 * @return `true` if `source` contains `other`; `false` otherwise.
 */
[[nodiscard, deprecated]] auto contains(const comp::aabb& source,
                                        const comp::aabb& other) noexcept
    -> bool;

/**
 * @brief Inserts an AABB instance into the AABB tree.
 *
 * @param registry the associated registry.
 * @param entity the entity identifier that will be added.
 * @param box the AABB instance that will be inserted.
 */
[[deprecated]] void insert(entt::registry& registry,
                           entt::entity entity,
                           const comp::aabb& box);

[[deprecated]] void remove(entt::registry& registry, entt::entity entity);

[[deprecated]] void update(entt::registry& registry,
                           entt::entity leafNodeEntity,
                           const comp::aabb& box);

// used to obtain collision candidates, could invoke some callback
template <typename T>
[[deprecated]] void query(entt::registry& registry,
                          entt::entity entity,
                          T&& callback)
{
  std::stack<entt::entity> stack;  // use pmr instead

  const auto& source = registry.get<comp::aabb_node>(entity);

  stack.push(registry.view<comp::aabb_root>().front());
  while (!stack.empty()) {
    const auto next = stack.top();
    stack.pop();

    if (next == entt::null) {
      continue;
    }

    const auto& nextNode = registry.get<comp::aabb_node>(next);
    if (overlaps(source.box, nextNode.box)) {
      if (nextNode.left == entt::null && &nextNode != &source) {
        callback(next);
      } else {
        stack.push(nextNode.left);
        stack.push(nextNode.right);
      }
    }
  }
}

}  // namespace wanderer::sys::aabb

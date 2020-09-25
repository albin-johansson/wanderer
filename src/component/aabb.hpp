#pragma once

#include <entt.hpp>

#include "vector2.hpp"

namespace wanderer::comp {

/**
 * @struct aabb
 * @brief Represents an AABB (Axis Aligned Bounding Box).
 *
 * @details An AABB is really just a fancy rectangle. They are mainly used
 * for collision detection systems, where trees can be built using AABBs in
 * order to decrease the complexity of finding potential collision candidates
 * . However, AABBs are not used for detailed collision detection. They are
 * only used to find potential collisions, which are then checked using more
 * exact collision detection systems.
 *
 * @note The "axis aligned" part is important, it means that the axes of the
 * rectangles must be aligned (parallel in relation to each other).
 * Otherwise, the systems that rely on AABBs won't work.
 *
 * @var aabb::min
 * The minimum x- and y-coordinates. Which are the coordinates of the
 * north-west corner of the box.
 * @var aabb::max
 * The maximum x- and y-coordinates. Which are the coordinates of the
 * south-east corner of the box.
 * @var aabb::center
 * The coordinates of the center point of the box.
 * @var aabb::area
 * The area of the box.
 *
 * @headerfile aabb.hpp
 */
struct aabb // FIXME this isn't really a component, no entities have it directly
{
  vector2f min;  // the NW corner coordinates
  vector2f max;  // the SE corner coordinates
  vector2f center;
  float area{};
};

/**
 * @struct aabb_node
 * @brief Represents a node in an AABB tree.
 *
 * @details This struct represents a node in the tree used by the AABB
 * systems. This component shouldn't be used directly.
 *
 * @var aabb_node::box
 * The associated AABB instance.
 * @var aabb_node::parent
 * The entity identifier of the parent node.
 * @var aabb_node::left
 * The entity identifier of the left child node.
 * @var aabb_node::right
 * The entity identifier of the right child node.
 *
 * @headerfile aabb.hpp
 */
struct aabb_node
{
  aabb box;
  entt::entity parent{entt::null};
  entt::entity left{entt::null};
  entt::entity right{entt::null};
};

/**
 * @struct aabb_root
 * @brief A tag type for the root of an AABB tree.
 *
 * @headerfile aabb.hpp
 */
struct aabb_root
{};

}  // namespace wanderer::comp

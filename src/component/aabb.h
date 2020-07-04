/**
 * @brief Provides the `AABB` component, along with related components.
 * @file aabb.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace wanderer::comp {

/**
 * @struct AABB
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
 * @var AABB::min
 * The minimum x- and y-coordinates. Which are the coordinates of the
 * north-west corner of the box.
 * @var AABB::max
 * The maximum x- and y-coordinates. Which are the coordinates of the
 * south-east corner of the box.
 * @var AABB::center
 * The coordinates of the center point of the box.
 * @var AABB::area
 * The area of the box.
 *
 * @headerfile aabb.h
 */
struct AABB {
  vector2f min;  // the NW corner coordinates
  vector2f max;  // the SE corner coordinates
  vector2f center;
  float area{};
};

/**
 * @struct AABBNode
 * @brief Represents a node in an AABB tree.
 *
 * @details This struct represents a node in the tree used by the AABB
 * systems. This component shouldn't be used directly.
 *
 * @var AABBNode::box
 * The associated AABB instance.
 * @var AABBNode::parent
 * The entity identifier of the parent node.
 * @var AABBNode::left
 * The entity identifier of the left child node.
 * @var AABBNode::right
 * The entity identifier of the right child node.
 *
 * @headerfile aabb.h
 */
struct AABBNode {
  AABB box;
  entt::entity parent{entt::null};
  entt::entity left{entt::null};
  entt::entity right{entt::null};
};

/**
 * @struct AABBRoot
 * @brief A tag type for the root of an AABB tree.
 *
 * @headerfile aabb.h
 */
struct AABBRoot {
};

}  // namespace wanderer::comp

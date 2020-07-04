#include "aabb_system.h"

#include <assert.hpp>

using wanderer::comp::AABB;
using wanderer::comp::AABBLeaf;
using wanderer::comp::AABBNode;
using wanderer::comp::AABBRoot;

/**
 * @brief
 * https://www.azurefromthetrenches.com/introductory-guide-to-aabb-tree-collision-detection/
 *
 *
 */

namespace wanderer::sys::aabb {
namespace {

auto merge(const AABB& fst, const AABB& snd) -> AABB
{
  AABB result;

  result.min.x = std::min(fst.min.x, snd.min.x);
  result.min.y = std::min(fst.min.y, snd.min.y);

  result.max.x = std::max(fst.max.x, snd.max.x);
  result.max.y = std::max(fst.max.y, snd.max.y);

  const auto width = result.max.x - result.min.x;
  const auto height = result.max.y - result.min.y;
  result.area = width * height;

  const auto centerX = result.min.x + (width / 2.0f);
  const auto centerY = result.min.y + (height / 2.0f);
  result.center = {centerX, centerY};

  return result;
}

auto find_best_place(entt::registry& registry,
                     const entt::entity rootEntity,
                     const AABBNode& originNode) -> entt::entity
{
  entt::entity currentEntity = rootEntity;

  const auto isLeaf = [&registry](const auto entity) {
    return registry.get<AABBNode>(entity).left == entt::null;
  };

  while (!isLeaf(currentEntity)) {
    const auto& currentNode = registry.get<AABBNode>(currentEntity);
    const auto& leftChildNode = registry.get<AABBNode>(currentNode.left);
    const auto& rightChildNode = registry.get<AABBNode>(currentNode.right);

    const auto combined = merge(currentNode.box, originNode.box);

    auto newParentNodeCost = 2.0f * combined.area;
    auto minPushDownCost = 2.0f * (combined.area - currentNode.box.area);

    // use the costs to figure out whether to create a new parent here or
    // descend

    const auto calc_cost = [&registry, &originNode, minPushDownCost](
                               const auto entity, const auto& node) -> float {
      const auto merged = merge(originNode.box, node);
      if (registry.has<AABBLeaf>(entity)) {
        return merged.area + minPushDownCost;
      } else {
        return (merged.area - node.area) + minPushDownCost;
      }
    };

    const auto costLeft = calc_cost(currentNode.left, leftChildNode.box);
    const auto costRight = calc_cost(currentNode.right, rightChildNode.box);

    // if the cost of creating a new parent node here is less than descending
    // in either direction then we know we need to create a new parent node,
    // errrr, here and attach the leaf to that

    if (newParentNodeCost < costLeft && newParentNodeCost < costRight) {
      break;
    } else {
      if (costLeft < costRight) {
        currentEntity = currentNode.left;
      } else {
        currentEntity = currentNode.right;
      }
    }
  }
  return currentEntity;
}

void fix_upwards_tree(entt::registry& registry, const entt::entity entity)
{
  entt::entity current = entity;
  while (current != entt::null) {
    auto& currentNode = registry.get<AABBNode>(current);

    BOOST_ASSERT_MSG(currentNode.left != entt::null,
                     "AABB node must have children if it isn't a leaf!");
    BOOST_ASSERT_MSG(currentNode.right != entt::null,
                     "AABB node must have children if it isn't a leaf!");

    const auto& leftChildNode = registry.get<AABBNode>(currentNode.left);
    const auto& rightChildNode = registry.get<AABBNode>(currentNode.left);

    currentNode.box = merge(leftChildNode.box, rightChildNode.box);

    current = currentNode.parent;
  }
}

void insert_leaf(entt::registry& registry,
                 const entt::entity originEntity,
                 const entt::entity originSibling)
{
  AABBNode& originSiblingNode = registry.get<AABBNode>(originSibling);

  const auto oldParent = originSiblingNode.parent;
  const auto newParent = registry.create();

  auto& originNode = registry.get<AABBNode>(originEntity);

  // the new parents aabb is the leaf aabb combined with it's siblings aabb
  auto& newParentNode = registry.emplace<AABBNode>(newParent);
  newParentNode.parent = oldParent;
  newParentNode.box = merge(originNode.box, originSiblingNode.box);
  newParentNode.left = originSibling;
  newParentNode.right = originEntity;

  originNode.parent = newParent;
  originSiblingNode.parent = newParent;

  if (oldParent == entt::null) {
    // the old parent was the root and so this is now the root
    registry.clear<AABBRoot>();
    registry.emplace<AABBRoot>(newParent);
  } else {
    // the old parent was not the root and so we need to patch the left or
    // right index to point to the new node
    auto& oldParentNode = registry.get<AABBNode>(oldParent);
    if (oldParentNode.left == originSibling) {
      oldParentNode.left = newParent;
    } else {
      oldParentNode.right = newParent;
    }
  }
}

}  // namespace

auto create_box(const centurion::FPoint& pos,
                const centurion::FArea& size) noexcept -> comp::AABB
{
  AABB result;

  result.min.x = pos.x();
  result.min.y = pos.y();

  result.max.x = pos.x() + size.width;
  result.max.y = pos.y() + size.height;

  result.center.x = pos.x() + (size.width / 2.0f);
  result.center.y = pos.y() + (size.height / 2.0f);
  result.area = size.width * size.height;

  return comp::AABB();
}

auto overlaps(const AABB& fst, const AABB& snd) -> bool
{
  return (fst.max.x > snd.min.x) && (fst.min.x < snd.max.x) &&
         (fst.max.y > snd.min.y) && (fst.min.y < snd.max.y);
}

void insert(entt::registry& registry,
            const entt::entity originEntity,
            const comp::AABB& box)
{
  // TODO THIS CAN BE DONE BY CONNECTING REGISTRY AS LISTENER

  BOOST_ASSERT_MSG(!registry.has<AABBRoot>(originEntity),
                   "Entity is already tagged as AABB root!");
  BOOST_ASSERT_MSG(!registry.has<AABBNode>(originEntity),
                   "Entity is already an AABB node!");
  BOOST_ASSERT_MSG(!registry.has<AABBLeaf>(originEntity),
                   "Entity is already an AABB leaf!");

  //  const auto rootView = registry.view<AABBRoot>();
  //  if (rootView.empty()) {
  //    registry.emplace<AABBRoot>(originEntity);
  //    registry.emplace<AABBNode>(originEntity);
  //    return;
  //  }

  //  BOOST_ASSERT_MSG(!registry.empty<AABBRoot>(), "There must be a root!");

  //  registry.emplace<AABBLeaf>(originEntity);
  auto& originNode = registry.emplace<AABBNode>(originEntity);
  originNode.box = box;

  BOOST_ASSERT(originNode.parent == entt::null);
  BOOST_ASSERT(originNode.left == entt::null);
  BOOST_ASSERT(originNode.right == entt::null);

  const auto rootView = registry.view<AABBRoot>();
  if (rootView.empty()) {
    registry.emplace<AABBRoot>(originEntity);
    return;
  }

  auto rootEntity = rootView.front();

  const auto foundEntity = find_best_place(registry, rootEntity, originNode);

  insert_leaf(registry, originEntity, foundEntity);

  fix_upwards_tree(registry, originNode.parent);
}

void query(entt::registry&, entt::entity)
{
  //  const auto& source = registry.get<AABBNode>(entity);
  //
  //  const auto view = registry.view<AABBNode>();
  //
  //  for (const auto e : view) {
  //    auto& node = view.get(e);
  //
  //    if (registry.has<AABBLeaf>(e)) {
  //      // TODO check collision
  //
  //    } else {
  //      const auto& left = registry.get<AABBNode>(node.left);
  //      const auto& right = registry.get<AABBNode>(node.right);
  //    }
  //  }
}

}  // namespace wanderer::sys::aabb

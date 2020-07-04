#include "aabb_system.h"

#include <algorithm>
#include <assert.hpp>

using wanderer::comp::AABB;
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

void fix_upwards_tree(entt::registry& registry, entt::entity treeNodeEntity)
{
  while (treeNodeEntity != entt::null) {
    auto& treeNode = registry.get<AABBNode>(treeNodeEntity);

    BOOST_ASSERT_MSG(
        treeNode.left != entt::null && treeNode.right != entt::null,
        "Every node should be a parent!");

    // fix height and area
    const auto& leftNode = registry.get<AABBNode>(treeNode.left);
    const auto& rightNode = registry.get<AABBNode>(treeNode.right);

    treeNode.box = merge(leftNode.box, rightNode.box);

    treeNodeEntity = treeNode.parent;
  }
}

}  // namespace

auto merge(const AABB& fst, const AABB& snd) noexcept -> AABB
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

auto make_aabb(const centurion::FPoint& pos,
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

  return result;
}

auto overlaps(const AABB& fst, const AABB& snd) -> bool
{
  return (fst.max.x > snd.min.x) && (fst.min.x < snd.max.x) &&
         (fst.max.y > snd.min.y) && (fst.min.y < snd.max.y);
}

void insert_leaf(entt::registry& registry, const entt::entity leafNodeEntity)
{
  // make sure we're inserting a new leaf
  const auto& node = registry.get<AABBNode>(leafNodeEntity);
  BOOST_ASSERT(node.parent == entt::null);
  BOOST_ASSERT(node.left == entt::null);
  BOOST_ASSERT(node.right == entt::null);

  // if the tree is empty then we make the root the leaf
  if (registry.empty<AABBRoot>()) {
    registry.clear<AABBRoot>();
    registry.emplace<AABBRoot>(leafNodeEntity);
    return;
  }

  // search for the best place to put the new leaf in the tree
  // we use surface area and depth as search heuristics
  auto treeNodeEntity = registry.view<AABBRoot>().front();
  auto& leafNode = registry.get<AABBNode>(leafNodeEntity);

  const auto isLeaf = [&registry](const auto entity) noexcept -> bool {
    const auto& node = registry.get<AABBNode>(entity);
    return node.left == entt::null;
  };

  while (!isLeaf(treeNodeEntity)) {
    // because of the test in the while loop above we know we are never a leaf
    // inside it
    const auto& treeNode = registry.get<AABBNode>(treeNodeEntity);
    const auto leftNodeEntity = treeNode.left;
    const auto rightNodeEntity = treeNode.right;
    const auto& leftNode = registry.get<AABBNode>(leftNodeEntity);
    const auto& rightNode = registry.get<AABBNode>(rightNodeEntity);

    const auto combined = merge(treeNode.box, leafNode.box);

    float newParentNodeCost = 2.0f * combined.area;
    float minimumPushDownCost = 2.0f * (combined.area - treeNode.box.area);

    const auto getCost = [&](const auto nodeEntity) -> float {
      const auto& node = registry.get<AABBNode>(nodeEntity);
      if (isLeaf(nodeEntity)) {
        return merge(leafNode.box, node.box).area + minimumPushDownCost;
      } else {
        return (merge(leafNode.box, node.box).area - node.box.area) +
               minimumPushDownCost;
      }
    };

    const auto costLeft = getCost(leftNodeEntity);
    const auto costRight = getCost(rightNodeEntity);

    // if the cost of creating a new parent node here is less than descending in
    // either direction then we know we need to create a new parent node, errrr,
    // here and attach the leaf to that
    if (newParentNodeCost < costLeft && newParentNodeCost < costRight) {
      break;
    }

    // otherwise descend in the cheapest direction
    if (costLeft < costRight) {
      treeNodeEntity = leftNodeEntity;
    } else {
      treeNodeEntity = rightNodeEntity;
    }
  }

  // the leafs sibling is going to be the node we found above and we are going
  // to create a new parent node and attach the leaf and this item
  const auto leafSiblingEntity = treeNodeEntity;
  auto& leafSiblingNode = registry.get<AABBNode>(leafSiblingEntity);

  const auto oldParentEntity = leafSiblingNode.parent;

  const auto newParentEntity = registry.create();
  auto& newParent = registry.emplace<AABBNode>(newParentEntity);
  newParent.parent = oldParentEntity;

  // the new parents aabb is the leaf aabb combined with  it's siblings aabb
  newParent.box = merge(leafNode.box, leafSiblingNode.box);

  newParent.left = leafSiblingEntity;
  newParent.right = leafNodeEntity;
  leafNode.parent = newParentEntity;
  leafSiblingNode.parent = newParentEntity;

  if (oldParentEntity == entt::null) {
    // the old parent was the root and so this is now the root
    registry.clear<AABBRoot>();
    registry.emplace<AABBRoot>(newParentEntity);
  } else {
    // the old parent was not the root and so we need to patch the left or right
    // index to point to the new node
    auto& oldParentNode = registry.get<AABBNode>(oldParentEntity);
    if (oldParentNode.left == leafSiblingEntity) {
      oldParentNode.left = newParentEntity;
    } else {
      oldParentNode.right = newParentEntity;
    }
  }

  // finally we need to walk back up the tree fixing heights and areas
  fix_upwards_tree(registry, leafNode.parent);
}

void insert(entt::registry& registry,
            const entt::entity originEntity,
            const comp::AABB& box)
{
  const auto nodeEntity = registry.create();
  auto& node = registry.emplace<AABBNode>(nodeEntity);
  node.box = box;

  insert_leaf(registry, nodeEntity);
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

#include "aabb_system.hpp"

#include <algorithm>  // min, max
#include <cassert>    // assert

/**
 * @brief
 * https://www.azurefromthetrenches.com/introductory-guide-to-aabb-tree-collision-detection/
 *
 *
 */

namespace wanderer::sys::aabb {
namespace {

void fix_upwards_tree(entt::registry& registry,
                      entt::entity treeNodeEntity) noexcept
{
  while (treeNodeEntity != entt::null) {
    auto& treeNode = registry.get<comp::aabb_node>(treeNodeEntity);

    // Every node should be a parent
    assert(treeNode.left != entt::null && treeNode.right != entt::null);

    // fix height and area
    const auto& leftNode = registry.get<comp::aabb_node>(treeNode.left);
    const auto& rightNode = registry.get<comp::aabb_node>(treeNode.right);

    treeNode.box = merge(leftNode.box, rightNode.box);

    treeNodeEntity = treeNode.parent;
  }
}

void insert_leaf(entt::registry& registry,
                 const entt::entity leafNodeEntity) noexcept
{
  // make sure we're inserting a new leaf
  const auto& node = registry.get<comp::aabb_node>(leafNodeEntity);
  assert(node.parent == entt::null);
  assert(node.left == entt::null);
  assert(node.right == entt::null);

  // if the tree is empty then we make the root the leaf
  if (registry.empty<comp::aabb_root>()) {
    registry.clear<comp::aabb_root>();
    registry.emplace<comp::aabb_root>(leafNodeEntity);
    return;
  }

  // search for the best place to put the new leaf in the tree
  // we use surface area and depth as search heuristics
  auto treeNodeEntity = registry.view<comp::aabb_root>().front();
  auto& leafNode = registry.get<comp::aabb_node>(leafNodeEntity);

  const auto isLeaf = [&registry](const auto entity) noexcept -> bool {
    const auto& node = registry.get<comp::aabb_node>(entity);
    return node.left == entt::null;
  };

  while (!isLeaf(treeNodeEntity)) {
    // because of the test in the while loop above we know we are never a leaf
    // inside it
    const auto& treeNode = registry.get<comp::aabb_node>(treeNodeEntity);
    const auto leftNodeEntity = treeNode.left;
    const auto rightNodeEntity = treeNode.right;
    const auto combined = merge(treeNode.box, leafNode.box);

    float newParentNodeCost = 2.0f * combined.area;
    float minimumPushDownCost = 2.0f * (combined.area - treeNode.box.area);

    const auto getCost = [&](const auto nodeEntity) noexcept -> float {
      const auto& node = registry.get<comp::aabb_node>(nodeEntity);
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
  auto& leafSiblingNode = registry.get<comp::aabb_node>(leafSiblingEntity);

  const auto oldParentEntity = leafSiblingNode.parent;

  const auto newParentEntity = registry.create();
  auto& newParent = registry.emplace<comp::aabb_node>(newParentEntity);
  newParent.parent = oldParentEntity;

  // the new parents aabb is the leaf aabb combined with  it's siblings aabb
  newParent.box = merge(leafNode.box, leafSiblingNode.box);

  newParent.left = leafSiblingEntity;
  newParent.right = leafNodeEntity;
  leafNode.parent = newParentEntity;
  leafSiblingNode.parent = newParentEntity;

  if (oldParentEntity == entt::null) {
    // the old parent was the root and so this is now the root
    registry.clear<comp::aabb_root>();
    registry.emplace<comp::aabb_root>(newParentEntity);
  } else {
    // the old parent was not the root and so we need to patch the left or right
    // index to point to the new node
    auto& oldParentNode = registry.get<comp::aabb_node>(oldParentEntity);
    if (oldParentNode.left == leafSiblingEntity) {
      oldParentNode.left = newParentEntity;
    } else {
      oldParentNode.right = newParentEntity;
    }
  }

  // finally we need to walk back up the tree fixing heights and areas
  fix_upwards_tree(registry, leafNode.parent);
}

void remove_leaf(entt::registry& registry,
                 const entt::entity leafNodeEntity) noexcept
{
  // if the leaf is the root then we can just clear the root pointer and return
  if (registry.view<comp::aabb_root>().front() == leafNodeEntity) {
    registry.clear<comp::aabb_root>();
    return;
  }

  auto& leafNode = registry.get<comp::aabb_node>(leafNodeEntity);
  const auto parentNodeEntity = leafNode.parent;

  // Parent node cannot be null
  assert(parentNodeEntity != entt::null);

  const auto& parentNode = registry.get<comp::aabb_node>(leafNode.parent);
  const auto grandParentEntity = parentNode.parent;
  const auto siblingNodeEntity =
      parentNode.left == leafNodeEntity ? parentNode.right : parentNode.left;

  // The node must have a sibling
  assert(siblingNodeEntity != entt::null);

  auto& siblingNode = registry.get<comp::aabb_node>(siblingNodeEntity);
  if (grandParentEntity != entt::null) {
    // if we have a grand parent (i.e. the parent is not the root) then destroy
    // the parent and connect the sibling to the grandparent in its place
    auto& grandParentNode = registry.get<comp::aabb_node>(grandParentEntity);
    if (grandParentNode.left == parentNodeEntity) {
      grandParentNode.left = siblingNodeEntity;
    } else {
      grandParentNode.right = siblingNodeEntity;
    }

    siblingNode.parent = grandParentEntity;
    // FIXME registry.destroy(parentNodeEntity); // might be undesirable
    fix_upwards_tree(registry, grandParentEntity);
  } else {
    // if we have no grandparent then the parent is the root and so our sibling
    // becomes the root and has it's parent removed
    registry.clear<comp::aabb_root>();
    registry.emplace<comp::aabb_root>(siblingNodeEntity);
    siblingNode.parent = entt::null;
  }
  leafNode.parent = entt::null;
}

}  // namespace

void validate(comp::aabb& aabb) noexcept
{
  const auto width = aabb.max.x() - aabb.min.x();
  const auto height = aabb.max.y() - aabb.min.y();

  aabb.center = {aabb.min.x() + (width / 2.0f), aabb.min.y() + (height / 2.0f)};
  aabb.area = width * height;
}

auto make_aabb(const cen::fpoint& pos, const cen::farea& size) noexcept
    -> comp::aabb
{
  comp::aabb result;

  result.min = {pos.x(), pos.y()};
  result.max = {pos.x() + size.width, pos.y() + size.height};

  validate(result);

  return result;
}

auto merge(const comp::aabb& fst, const comp::aabb& snd) noexcept -> comp::aabb
{
  comp::aabb result;

  result.min.set_x(std::min(fst.min.x(), snd.min.x()));
  result.min.set_y(std::min(fst.min.y(), snd.min.y()));

  result.max.set_x(std::max(fst.max.x(), snd.max.x()));
  result.max.set_y(std::max(fst.max.y(), snd.max.y()));

  const auto width = result.max.x() - result.min.x();
  const auto height = result.max.y() - result.min.y();
  result.area = width * height;

  const auto centerX = result.min.x() + (width / 2.0f);
  const auto centerY = result.min.y() + (height / 2.0f);
  result.center = {centerX, centerY};

  return result;
}

auto overlaps(const comp::aabb& fst, const comp::aabb& snd) noexcept -> bool
{
  return (fst.max.x() > snd.min.x()) && (fst.min.x() < snd.max.x()) &&
         (fst.max.y() > snd.min.y()) && (fst.min.y() < snd.max.y());
}

auto contains(const comp::aabb& source, const comp::aabb& other) noexcept
    -> bool
{
  return other.min.x() >= source.min.x() && other.max.x() <= source.max.x() &&
         other.min.y() >= source.min.y() && other.max.y() <= source.max.y();
}

void insert(entt::registry& registry,
            const entt::entity entity,
            const comp::aabb& box) noexcept
{
  auto& node = registry.emplace<comp::aabb_node>(entity);
  node.box = box;

  insert_leaf(registry, entity);
}

void update(entt::registry& registry,
            entt::entity leafNodeEntity,
            const comp::aabb& box) noexcept
{
  auto& node = registry.get<comp::aabb_node>(leafNodeEntity);

  if (contains(node.box, box)) {
    return;
  }

  remove_leaf(registry, leafNodeEntity);
  node.box = box;
  insert_leaf(registry, leafNodeEntity);
}

}  // namespace wanderer::sys::aabb

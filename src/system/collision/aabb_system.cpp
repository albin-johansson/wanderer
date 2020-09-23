#include "aabb_system.hpp"

#include <algorithm>
#include <assert.hpp>

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
    auto& treeNode = registry.get<comp::AABBNode>(treeNodeEntity);

    BOOST_ASSERT_MSG(
        treeNode.left != entt::null && treeNode.right != entt::null,
        "Every node should be a parent!");

    // fix height and area
    const auto& leftNode = registry.get<comp::AABBNode>(treeNode.left);
    const auto& rightNode = registry.get<comp::AABBNode>(treeNode.right);

    treeNode.box = merge(leftNode.box, rightNode.box);

    treeNodeEntity = treeNode.parent;
  }
}

void insert_leaf(entt::registry& registry,
                 const entt::entity leafNodeEntity) noexcept
{
  // make sure we're inserting a new leaf
  const auto& node = registry.get<comp::AABBNode>(leafNodeEntity);
  BOOST_ASSERT(node.parent == entt::null);
  BOOST_ASSERT(node.left == entt::null);
  BOOST_ASSERT(node.right == entt::null);

  // if the tree is empty then we make the root the leaf
  if (registry.empty<comp::AABBRoot>()) {
    registry.clear<comp::AABBRoot>();
    registry.emplace<comp::AABBRoot>(leafNodeEntity);
    return;
  }

  // search for the best place to put the new leaf in the tree
  // we use surface area and depth as search heuristics
  auto treeNodeEntity = registry.view<comp::AABBRoot>().front();
  auto& leafNode = registry.get<comp::AABBNode>(leafNodeEntity);

  const auto isLeaf = [&registry](const auto entity) noexcept -> bool {
    const auto& node = registry.get<comp::AABBNode>(entity);
    return node.left == entt::null;
  };

  while (!isLeaf(treeNodeEntity)) {
    // because of the test in the while loop above we know we are never a leaf
    // inside it
    const auto& treeNode = registry.get<comp::AABBNode>(treeNodeEntity);
    const auto leftNodeEntity = treeNode.left;
    const auto rightNodeEntity = treeNode.right;
    const auto combined = merge(treeNode.box, leafNode.box);

    float newParentNodeCost = 2.0f * combined.area;
    float minimumPushDownCost = 2.0f * (combined.area - treeNode.box.area);

    const auto getCost = [&](const auto nodeEntity) noexcept -> float {
      const auto& node = registry.get<comp::AABBNode>(nodeEntity);
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
  auto& leafSiblingNode = registry.get<comp::AABBNode>(leafSiblingEntity);

  const auto oldParentEntity = leafSiblingNode.parent;

  const auto newParentEntity = registry.create();
  auto& newParent = registry.emplace<comp::AABBNode>(newParentEntity);
  newParent.parent = oldParentEntity;

  // the new parents aabb is the leaf aabb combined with  it's siblings aabb
  newParent.box = merge(leafNode.box, leafSiblingNode.box);

  newParent.left = leafSiblingEntity;
  newParent.right = leafNodeEntity;
  leafNode.parent = newParentEntity;
  leafSiblingNode.parent = newParentEntity;

  if (oldParentEntity == entt::null) {
    // the old parent was the root and so this is now the root
    registry.clear<comp::AABBRoot>();
    registry.emplace<comp::AABBRoot>(newParentEntity);
  } else {
    // the old parent was not the root and so we need to patch the left or right
    // index to point to the new node
    auto& oldParentNode = registry.get<comp::AABBNode>(oldParentEntity);
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
  if (registry.view<comp::AABBRoot>().front() == leafNodeEntity) {
    registry.clear<comp::AABBRoot>();
    return;
  }

  auto& leafNode = registry.get<comp::AABBNode>(leafNodeEntity);
  const auto parentNodeEntity = leafNode.parent;

  BOOST_ASSERT_MSG(parentNodeEntity != entt::null, "Parent was null!");

  const auto& parentNode = registry.get<comp::AABBNode>(leafNode.parent);
  const auto grandParentEntity = parentNode.parent;
  const auto siblingNodeEntity =
      parentNode.left == leafNodeEntity ? parentNode.right : parentNode.left;

  BOOST_ASSERT_MSG(siblingNodeEntity != entt::null, "Must have sibling!");

  auto& siblingNode = registry.get<comp::AABBNode>(siblingNodeEntity);
  if (grandParentEntity != entt::null) {
    // if we have a grand parent (i.e. the parent is not the root) then destroy
    // the parent and connect the sibling to the grandparent in its place
    auto& grandParentNode = registry.get<comp::AABBNode>(grandParentEntity);
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
    registry.clear<comp::AABBRoot>();
    registry.emplace<comp::AABBRoot>(siblingNodeEntity);
    siblingNode.parent = entt::null;
  }
  leafNode.parent = entt::null;
}

}  // namespace

void validate(comp::AABB& aabb) noexcept
{
  const auto width = aabb.max.x - aabb.min.x;
  const auto height = aabb.max.y - aabb.min.y;

  aabb.center.x = aabb.min.x + (width / 2.0f);
  aabb.center.y = aabb.min.y + (height / 2.0f);

  aabb.area = width * height;
}

auto make_aabb(const cen::fpoint& pos, const cen::farea& size) noexcept
    -> comp::AABB
{
  comp::AABB result;

  result.min.x = pos.x();
  result.min.y = pos.y();

  result.max.x = pos.x() + size.width;
  result.max.y = pos.y() + size.height;

  validate(result);

  //  result.center.x = pos.x() + (size.width / 2.0f);
  //  result.center.y = pos.y() + (size.height / 2.0f);
  //  result.area = size.width * size.height;

  return result;
}

auto merge(const comp::AABB& fst, const comp::AABB& snd) noexcept -> comp::AABB
{
  comp::AABB result;

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

auto overlaps(const comp::AABB& fst, const comp::AABB& snd) noexcept -> bool
{
  return (fst.max.x > snd.min.x) && (fst.min.x < snd.max.x) &&
         (fst.max.y > snd.min.y) && (fst.min.y < snd.max.y);
}

auto contains(const comp::AABB& source, const comp::AABB& other) noexcept
    -> bool
{
  return other.min.x >= source.min.x && other.max.x <= source.max.x &&
         other.min.y >= source.min.y && other.max.y <= source.max.y;
}

void insert(entt::registry& registry,
            const entt::entity entity,
            const comp::AABB& box) noexcept
{
  auto& node = registry.emplace<comp::AABBNode>(entity);
  node.box = box;

  insert_leaf(registry, entity);
}

void update(entt::registry& registry,
            entt::entity leafNodeEntity,
            const comp::AABB& box) noexcept
{
  auto& node = registry.get<comp::AABBNode>(leafNodeEntity);

  if (contains(node.box, box)) {
    return;
  }

  remove_leaf(registry, leafNodeEntity);
  node.box = box;
  insert_leaf(registry, leafNodeEntity);
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

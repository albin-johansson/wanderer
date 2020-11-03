#include "aabb_tree.hpp"

#include <array>            // array
#include <cassert>          // assert
#include <cstddef>          // byte
#include <deque>            // deque
#include <memory_resource>  // monotonic_buffer_resource
#include <stack>            // stack

namespace wanderer {
namespace {

[[nodiscard]] auto get_left_cost(const aabb_node& left,
                                 const aabb_node& leaf,
                                 float minimumCost) -> float
{
  if (is_leaf(left)) {
    return merge(leaf.box, left.box).area + minimumCost;
  } else {
    const auto newLeftAabb = merge(leaf.box, left.box);
    return (newLeftAabb.area - left.box.area) + minimumCost;
  }
}

[[nodiscard]] auto get_right_cost(const aabb_node& right,
                                  const aabb_node& leaf,
                                  float minimumCost) -> float
{
  if (is_leaf(right)) {
    return merge(leaf.box, right.box).area + minimumCost;
  } else {
    const auto newRightAabb = merge(leaf.box, right.box);
    return (newRightAabb.area - right.box.area) + minimumCost;
  }
}

}  // namespace

aabb_tree::aabb_tree()
{
  m_nodes.reserve(m_nodeCapacity);
  m_allocatedNodes = m_nodeCapacity;

  const auto size = static_cast<int>(m_nodeCapacity);
  for (int index = 0; index < size; ++index) {
    auto& node = m_nodes.emplace_back();
    node.next = index + 1;
  }

  m_nodes.at(size - 1).next = std::nullopt;
}

void aabb_tree::fix_upwards_tree(std::optional<int> nodeIndex)
{
  while (nodeIndex.has_value()) {
    auto& treeNode = m_nodes.at(nodeIndex.value());

    // every node should be a parent
    assert(treeNode.left.has_value() && treeNode.right.has_value());

    // fix height and area
    const auto& leftNode = m_nodes.at(treeNode.left.value());
    const auto& rightNode = m_nodes.at(treeNode.right.value());
    treeNode.box = merge(leftNode.box, rightNode.box);

    nodeIndex = treeNode.parent;
  }
}

auto aabb_tree::allocate_node() -> int
{
  // if we have no free tree nodes then grow the pool
  if (!m_nextFreeNodeIndex.has_value()) {
    assert(m_allocatedNodes == m_nodeCapacity);

    m_nodeCapacity += m_growthSize;
    m_nodes.resize(m_nodeCapacity);
    for (int nodeIndex = m_allocatedNodes; nodeIndex < m_nodeCapacity;
         ++nodeIndex) {
      auto& node = m_nodes.at(nodeIndex);
      node.next = nodeIndex + 1;
    }
    m_nodes.at(m_nodeCapacity - 1).next = std::nullopt;
    m_nextFreeNodeIndex = m_allocatedNodes;
  }

  const auto nodeIndex = m_nextFreeNodeIndex.value();
  auto& allocatedNode = m_nodes.at(nodeIndex);
  m_nextFreeNodeIndex = allocatedNode.next;
  ++m_allocatedNodes;

  return nodeIndex;
}

void aabb_tree::deallocate_node(int nodeIndex)
{
  auto& deallocatedNode = m_nodes.at(nodeIndex);
  deallocatedNode.next = m_nextFreeNodeIndex;
  m_nextFreeNodeIndex = nodeIndex;
  --m_allocatedNodes;
}

[[nodiscard]] auto aabb_tree::find_best_insertion_position(
    const aabb_node& leafNode) -> int
{
  auto treeNodeIndex = m_rootIndex.value();
  while (!is_leaf(m_nodes.at(treeNodeIndex))) {
    // because of the test in the while loop above we know we are never a leaf
    // inside it
    const auto& treeNode = m_nodes.at(treeNodeIndex);
    const auto leftNodeIndex = treeNode.left.value();
    const auto rightNodeIndex = treeNode.right.value();
    const auto& leftNode = m_nodes.at(leftNodeIndex);
    const auto& rightNode = m_nodes.at(rightNodeIndex);

    const auto combined = merge(treeNode.box, leafNode.box);

    const auto newParentNodeCost = 2.0f * combined.area;
    const auto minimumPushDownCost = 2.0f * (combined.area - treeNode.box.area);

    // use the costs to figure out whether to create a new parent here or
    // descend
    const auto costLeft =
        get_left_cost(leftNode, leafNode, minimumPushDownCost);
    const auto costRight =
        get_right_cost(rightNode, leafNode, minimumPushDownCost);

    // if the cost of creating a new parent node here is less than descending in
    // either direction then we know we need to create a new parent node, errrr,
    // here and attach the leaf to that
    if (newParentNodeCost < costLeft && newParentNodeCost < costRight) {
      break;
    }

    // otherwise descend in the cheapest direction
    if (costLeft < costRight) {
      treeNodeIndex = leftNodeIndex;
    } else {
      treeNodeIndex = rightNodeIndex;
    }
  }

  return treeNodeIndex;
}

void aabb_tree::insert_leaf(int leafIndex)
{
  // make sure we're inserting a new leaf
  assert(!m_nodes.at(leafIndex).parent);
  assert(!m_nodes.at(leafIndex).left);
  assert(!m_nodes.at(leafIndex).right);

  // if the tree is empty then we make the root the leaf
  if (!m_rootIndex) {
    m_rootIndex = leafIndex;
    return;
  }

  // search for the best place to put the new leaf in the tree
  // we use surface area and depth as search heuristics
  auto& leafNode = m_nodes.at(leafIndex);
  const auto foundIndex = find_best_insertion_position(leafNode);

  // the leafs sibling is going to be the node we found above and we are going
  // to create a new parent node and attach the leaf and this item
  const auto leafSiblingIndex = foundIndex;
  auto& leafSibling = m_nodes.at(leafSiblingIndex);

  const auto oldParentIndex = leafSibling.parent;
  const auto newParentIndex = allocate_node();

  auto& newParent = m_nodes.at(newParentIndex);
  newParent.parent = oldParentIndex;
  // the new parents aabb is the leaf aabb combined with it's siblings aabb
  newParent.box = merge(leafNode.box, leafSibling.box);
  newParent.left = leafSiblingIndex;
  newParent.right = leafIndex;
  leafNode.parent = newParentIndex;
  leafSibling.parent = newParentIndex;

  if (!oldParentIndex.has_value()) {
    // the old parent was the root and so this is now the root
    m_rootIndex = newParentIndex;
  } else {
    // the old parent was not the root and so we need to patch the left or right
    // index to point to the new node
    auto& oldParent = m_nodes.at(oldParentIndex.value());
    if (oldParent.left == leafSiblingIndex) {
      oldParent.left = newParentIndex;
    } else {
      oldParent.right = newParentIndex;
    }
  }

  // finally we need to walk back up the tree fixing heights and areas
  fix_upwards_tree(leafNode.parent.value());
}

void aabb_tree::remove_leaf(int leafIndex)
{
  // if the leaf is the root then we can just clear the root pointer and return
  if (leafIndex == m_rootIndex) {
    m_rootIndex = std::nullopt;
    return;
  }

  auto& leafNode = m_nodes.at(leafIndex);

  const auto parentNodeIndex = leafNode.parent.value();
  const auto& parentNode = m_nodes.at(parentNodeIndex);

  const auto grandParentNodeIndex = parentNode.parent;

  const auto siblingNodeIndex =
      parentNode.left == leafIndex ? parentNode.right : parentNode.left;
  assert(siblingNodeIndex.has_value());  // we must have a sibling
  auto& siblingNode = m_nodes.at(*siblingNodeIndex);

  if (grandParentNodeIndex.has_value()) {
    // if we have a grand parent (i.e. the parent is not the root) then destroy
    // the parent and connect the sibling to the grandparent in its place
    auto& grandParentNode = m_nodes.at(*grandParentNodeIndex);
    if (grandParentNode.left == parentNodeIndex) {
      grandParentNode.left = siblingNodeIndex;
    } else {
      grandParentNode.right = siblingNodeIndex;
    }
    siblingNode.parent = grandParentNodeIndex;
    deallocate_node(parentNodeIndex);
    fix_upwards_tree(grandParentNodeIndex);
  } else {
    // if we have no grandparent then the parent is the root and so our sibling
    // becomes the root and has it's parent removed
    m_rootIndex = siblingNodeIndex;
    siblingNode.parent = std::nullopt;
    deallocate_node(parentNodeIndex);
  }

  leafNode.parent = std::nullopt;
}

void aabb_tree::update_leaf(int leafIndex, const aabb& box)
{
  auto& node = m_nodes.at(leafIndex);

  // if the node contains the new aabb then we just leave things
  if (contains(node.box, box)) {
    return;
  }

  remove_leaf(leafIndex);
  node.box = box;
  insert_leaf(leafIndex);
}

void aabb_tree::insert(entt::entity entity, const aabb& box)
{
  const auto nodeIndex = allocate_node();
  auto& node = m_nodes.at(nodeIndex);

  node.box = box;
  node.entity = entity;

  insert_leaf(nodeIndex);
  m_entities.emplace(entity, nodeIndex);
}

void aabb_tree::remove(entt::entity entity)
{
  const auto nodeIndex = m_entities.at(entity);
  remove_leaf(nodeIndex);
  deallocate_node(nodeIndex);
  m_entities.erase(entity);
}

void aabb_tree::update(entt::entity entity, const aabb& box)
{
  const auto nodeIndex = m_entities.at(entity);
  update_leaf(nodeIndex, box);
}

void aabb_tree::move_aabb(entt::entity entity, const vector2f& position)
{
  const auto oldBox = get_aabb(entity);

  aabb newBox;
  newBox.min = position;
  newBox.max = position + (oldBox.max - oldBox.min);

  const auto width = newBox.max.x() - newBox.min.x();
  const auto height = newBox.max.y() - newBox.min.y();
  newBox.area = width * height;

  update(entity, newBox);
}

}  // namespace wanderer

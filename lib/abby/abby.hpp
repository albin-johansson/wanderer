/*
 * MIT License
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
 *
 * This code was originally based on the AABB tree implementation in the Simple
 * Voxel Engine project, which can be found here:
 * https://github.com/JamesRandall/SimpleVoxelEngine. The Simple Voxel Engine
 * project also uses the MIT license.
 */

#ifndef ABBY__HEADER__GUARD_
#define ABBY__HEADER__GUARD_

#include <algorithm>        // min, max
#include <array>            // array
#include <cassert>          // assert
#include <cstddef>          // byte
#include <deque>            // deque
#include <map>              // map
#include <memory_resource>  // monotonic_buffer_resource
#include <optional>         // optional
#include <stack>            // stack
#include <vector>           // vector

namespace abby {

/**
 * \struct vec2
 *
 * \brief A very simple representation of a 2D vector.
 *
 * \tparam T the representation type used.
 *
 * \since 0.1.0
 *
 * \see fvec2
 * \see dvec2
 *
 * \headerfile abby.hpp
 */
template <typename T>
struct vec2 final
{
  T x{};  ///< The x-axis component.
  T y{};  ///< The y-axis component.
};

/**
 * \typedef point
 *
 * \brief An alias for `vec2` that represents a point.
 *
 * \since 0.1.0
 */
template <typename T>
using point = vec2<T>;

/**
 * \typedef size
 *
 * \brief An alias for `vec2` that represents a width and height.
 *
 * \since 0.1.0
 */
template <typename T>
using size = vec2<T>;

// clang-format off
vec2(float, float)       -> vec2<float>;
vec2(double, double)     -> vec2<double>;
vec2(int, int)           -> vec2<int>;
vec2(unsigned, unsigned) -> vec2<unsigned>;
// clang-format on

/**
 * \brief Adds two vectors and returns the result.
 *
 * \tparam T the representation type used by the vectors.
 *
 * \param lhs the left-hand side vector.
 * \param rhs the right-hand side vector.
 *
 * \return a vector that is the result of adding the components of the two
 * vectors.
 *
 * \since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator+(const vec2<T>& lhs,
                                       const vec2<T>& rhs) noexcept -> vec2<T>
{
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}

/**
 * \brief Subtracts two vectors and returns the result.
 *
 * \tparam T the representation type used by the vectors.
 *
 * \param lhs the left-hand side vector.
 * \param rhs the right-hand side vector.
 *
 * \return a vector that is the result of subtracting the components of the two
 * vectors.
 *
 * \since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator-(const vec2<T>& lhs,
                                       const vec2<T>& rhs) noexcept -> vec2<T>
{
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}

/**
 * \brief Indicates whether or not two vectors are equal.
 *
 * \tparam T the representation type used by the vectors.
 *
 * \param lhs the left-hand side vector.
 * \param rhs the right-hand side vector.
 *
 * \return `true` if the two vectors are equal; `false` otherwise.
 *
 * \since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const vec2<T>& lhs,
                                        const vec2<T>& rhs) noexcept -> bool
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

/**
 * \brief Indicates whether or not two vectors aren't equal.
 *
 * \tparam T the representation type used by the vectors.
 *
 * \param lhs the left-hand side vector.
 * \param rhs the right-hand side vector.
 *
 * \return `true` if the two vectors aren't equal; `false` otherwise.
 *
 * \since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const vec2<T>& lhs,
                                        const vec2<T>& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \struct aabb
 *
 * \brief Represents an AABB (Axis Aligned Bounding Box).
 *
 * \note This is really just a glorified rectangle.
 *
 * \tparam T the representation type of the components used by the AABB.
 *
 * \since 0.1.0
 *
 * \see faabb
 * \see daabb
 *
 * \headerfile abby.hpp
 */
template <typename T = float>
struct aabb final
{
  vec2<T> min;  ///< The top-left corner of the AABB.
  vec2<T> max;  ///< The bottom-right corner of the AABB.

  /**
   * \brief Indicates whether or not the supplied AABB is contained within the
   * invoked AABB.
   *
   * \note The supplied AABB is still considered to be contained within the
   * invoked AABB if the borders of the inner AABB are overlapping the borders
   * of the outer AABB.
   *
   * \param other the AABB to check.
   *
   * \return `true` if the supplied AABB is contained in the AABB; `false`
   * otherwise.
   *
   * \since 0.1.0
   */
  [[nodiscard]] constexpr auto contains(const aabb<T>& other) const noexcept
      -> bool
  {
    return (other.min.x >= min.x) && (other.max.x <= max.x) &&
           (other.min.y >= min.y) && (other.max.y <= max.y);
  }

  /**
   * \brief Indicates whether or not two AABBs are overlapping each other.
   *
   * \param other the other AABB to compare with.
   *
   * \return `true` if the two AABBs are overlapping each other; `false`
   * otherwise.
   *
   * \since 0.1.0
   */
  [[nodiscard]] constexpr auto overlaps(const aabb<T>& other) const noexcept
      -> bool
  {
    return (max.x > other.min.x) && (min.x < other.max.x) &&
           (max.y > other.min.y) && (min.y < other.max.y);
  }

  /**
   * \brief Returns the area of the AABB.
   *
   * \note The area is not stored in the object, so it is computed for every
   * invocation of this function. This is of course not an expensive operation,
   * but it is worth knowing.
   *
   * \return the area of the AABB.
   *
   * \since 0.1.0
   */
  [[nodiscard]] constexpr auto area() const noexcept -> T
  {
    const auto width = max.x - min.x;
    const auto height = max.y - min.y;
    return width * height;
  }
};

// clang-format off
aabb(vec2<float>, vec2<float>) -> aabb<float>;
aabb(vec2<int>, vec2<int>)     -> aabb<int>;
// clang-format on

/**
 * \brief Indicates whether or not two AABBs are equal.
 *
 * \tparam T the representation type used by the AABBs.
 *
 * \param lhs the left-hand side AABB.
 * \param rhs the right-hand side AABB.
 *
 * \return `true` if the two AABBs are equal; `false` otherwise.
 *
 * \since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const aabb<T>& lhs,
                                        const aabb<T>& rhs) noexcept -> bool
{
  return lhs.min == rhs.min && lhs.max == rhs.max;
}

/**
 * \brief Indicates whether or not two AABBs aren't equal.
 *
 * \tparam T the representation type used by the AABBs.
 *
 * \param lhs the left-hand side AABB.
 * \param rhs the right-hand side AABB.
 *
 * \return `true` if the two AABBs aren't equal; `false` otherwise.
 *
 * \since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const aabb<T>& lhs,
                                        const aabb<T>& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Creates and returns an AABB with the specified position and size.
 *
 * \details This is a convenience function for creating an AABB by specifying
 * the position and size, instead of the top-left and bottom-right corners.
 *
 * \tparam T the representation type used.
 *
 * \param position the position of the AABB (X and Y).
 * \param size the size of the AABB (width and height).
 *
 * \return an AABB at the specified position with the the specified size.
 *
 * \since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto make_aabb(const vec2<T>& position,
                                       const vec2<T>& size) -> aabb<T>
{
  aabb box;

  box.min = position;
  box.max = box.min + size;

  return box;
}

/**
 * \brief Returns an AABB that is the union of the supplied pair of AABBs.
 *
 * \tparam T the representation type used by the AABBs.
 *
 * \param fst the first AABB.
 * \param snd the second AABB.
 *
 * \return an AABB that is the union of the two supplied AABBs.
 *
 * \since 0.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto combine(const aabb<T>& fst,
                                     const aabb<T>& snd) noexcept -> aabb<T>
{
  aabb result;

  result.min.x = std::min(fst.min.x, snd.min.x);
  result.min.y = std::min(fst.min.y, snd.min.y);

  result.max.x = std::max(fst.max.x, snd.max.x);
  result.max.y = std::max(fst.max.y, snd.max.y);

  return result;
}

/**
 * \struct aabb_node
 *
 * \brief Represents a node in an AABB tree.
 *
 * \details Contains an AABB and the entity associated with the AABB, along
 * with tree information.
 *
 * \since 0.1.0
 *
 * \headerfile abby.hpp
 */
template <typename T, typename U = float>
struct aabb_node final
{
  T id;
  aabb<U> box;
  std::optional<int> parent;
  std::optional<int> left;
  std::optional<int> right;
  std::optional<int> next;

  /**
   * \brief Indicates whether or not the node is a leaf node.
   *
   * \details A node is a leaf node if it has no left child node.
   *
   * \return `true` if the node is a leaf node; `false` otherwise.
   *
   * \since 0.1.0
   */
  [[nodiscard]] constexpr auto is_leaf() const noexcept -> bool
  {
    return !left;
  }
};

/// \cond FALSE

namespace detail {

template <typename T, typename U>
[[nodiscard]] constexpr auto get_left_cost(const aabb_node<T, U>& left,
                                           const aabb_node<T, U>& leaf,
                                           float minimumCost) -> float
{
  if (left.is_leaf()) {
    return combine(leaf.box, left.box).area() + minimumCost;
  } else {
    const auto newLeftAabb = combine(leaf.box, left.box);
    return (newLeftAabb.area() - left.box.area()) + minimumCost;
  }
}

template <typename T, typename U>
[[nodiscard]] constexpr auto get_right_cost(const aabb_node<T, U>& right,
                                            const aabb_node<T, U>& leaf,
                                            float minimumCost) -> float
{
  if (right.is_leaf()) {
    return combine(leaf.box, right.box).area() + minimumCost;
  } else {
    const auto newRightAabb = combine(leaf.box, right.box);
    return (newRightAabb.area() - right.box.area()) + minimumCost;
  }
}

}  // namespace detail

/// \endcond

/**
 * \class aabb_tree
 *
 * \brief Represents a tree of AABBs used for efficient collision detection.
 *
 * \tparam Key the type of the keys associated with each node. Must be
 * comparable and preferable small and cheap to copy, e.g. `int`.
 * \tparam T the representation type used by the AABBs, should be a
 * floating-point type for best precision.
 *
 * \since 0.1.0
 *
 * \headerfile abby.hpp
 */
template <typename Key, typename T = float>
class aabb_tree final
{
  template <typename U>
  using pmr_stack = std::stack<U, std::pmr::deque<U>>;

 public:
  using key_type = Key;
  using size_type = std::size_t;
  using vector_type = vec2<T>;
  using aabb_type = aabb<T>;
  using node_type = aabb_node<key_type, T>;
  using index_type = int;

  aabb_tree()
  {
    m_nodes.reserve(m_nodeCapacity);
    m_allocatedNodes = m_nodeCapacity;

    const auto size = static_cast<int>(m_nodeCapacity);
    for (auto index = 0; index < size; ++index) {
      auto& node = m_nodes.emplace_back();
      node.next = index + 1;
    }

    m_nodes.at(size - 1).next.reset();
  }

  /**
   * \brief Inserts an AABB in the tree.
   *
   * \pre `key` cannot be in use at the time of invoking the function.
   *
   * \param key the ID that will be associated with the box.
   * \param box the AABB that will be added.
   *
   * \since 0.1.0
   */
  void insert(const key_type& key, const aabb_type& box)
  {
    assert(!m_indexMap.count(key));

    const auto index = allocate_node();
    auto& node = m_nodes.at(index);
    node.box = box;
    node.id = key;

    insert_leaf(index);
    m_indexMap.emplace(key, index);
  }

  /**
   * \brief Removes the AABB associated with the specified ID.
   *
   * \note This function has no effect if there is no AABB associated with the
   * specified ID.
   *
   * \param key the ID associated with the AABB that will be removed.
   *
   * \since 0.1.0
   */
  void erase(const key_type& key)
  {
    if (const auto it = m_indexMap.find(key); it != m_indexMap.end()) {
      const auto index = it->second;
      remove_leaf(index);
      deallocate_node(index);
      m_indexMap.erase(key);
    }
  }

  /**
   * \brief Replaces the AABB associated with the specified ID.
   *
   * \note This function has no effect if there is no AABB associated with the
   * specified ID.
   *
   * \param key the ID associated with the AABB that will be replaced.
   * \param box the new AABB that will be associated with the specified ID.
   *
   * \since 0.1.0
   */
  void replace(const key_type& key, const aabb_type& box)
  {
    if (const auto it = m_indexMap.find(key); it != m_indexMap.end()) {
      update_leaf(it->second, box);
    }
  }

  /**
   * \brief Updates the position of the AABB associated with the specified ID.
   *
   * \note This function has no effect if there is no AABB associated with the
   * specified ID.
   *
   * \param key the ID associated with the AABB that will be moved.
   * \param position the new position of the AABB associated with the specified
   * ID.
   *
   * \since 0.1.0
   */
  void set_position(const key_type& key, const vector_type& position)
  {
    if (!m_indexMap.count(key)) {
      return;
    }

    const auto previous = get_aabb(key);

    aabb newBox;
    newBox.min = position;
    newBox.max = position + (previous.max - previous.min);

    replace(key, newBox);
  }

  void query_collisions(const key_type&, std::nullptr_t) const = delete;

  /**
   * \brief Obtains collision candidates for the AABB associated with the
   * specified ID.
   *
   * \details In order to avoid unnecessary dynamic allocations, this function
   * returns the resulting collision candidates through an output iterator. This
   * means that it is possible to write collision candidates to both a stack
   * buffer and something like a `std::vector`.
   *
   * \details The output iterator can for instance be obtained using
   * `std::back_inserter`, if you're writing to a standard container.
   *
   * \tparam OutIterator the type of the output iterator.
   *
   * \param key the ID associated with the AABB to obtain collision candidates
   * for.
   * \param[out] iterator the output iterator used to write the collision
   * candidate IDs.
   *
   * \since 0.1.0
   */
  template <typename OutIterator>
  void query_collisions(const key_type& key, OutIterator iterator) const
  {
    if (!m_indexMap.count(key)) {
      return;
    }

    std::array<std::byte, sizeof(std::optional<int>) * 64> buffer;  // NOLINT
    std::pmr::monotonic_buffer_resource resource{buffer.data(), sizeof buffer};
    pmr_stack<std::optional<int>> stack{&resource};

    const auto& box = get_aabb(key);

    stack.push(m_rootIndex);
    while (!stack.empty()) {
      const auto nodeIndex = stack.top();
      stack.pop();

      if (!nodeIndex) {
        continue;
      }

      const auto& node = m_nodes.at(*nodeIndex);
      if (node.box.overlaps(box)) {
        if (node.is_leaf() && node.id != key) {
          *iterator = node.id;
          ++iterator;
        } else {
          stack.push(node.left);
          stack.push(node.right);
        }
      }
    }
  }

  /**
   * \brief Returns the AABB associated with the specified ID.
   *
   * \param key the ID associated with the desired AABB.
   *
   * \return the AABB associated with the specified ID.
   *
   * \throws if there is no AABB associated with the supplied ID.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto get_aabb(const key_type& key) const -> const aabb_type&
  {
    return m_nodes.at(static_cast<size_type>(m_indexMap.at(key))).box;
  }

  /**
   * \brief Returns the amount of AABBs stored in the tree.
   *
   * \note The returned value is not necessarily the amount of _nodes_ in the
   * tree.
   *
   * \return the current amount of AABBs stored in the tree.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto size() const noexcept -> size_type
  {
    return m_indexMap.size();
  }

  /**
   * \brief Indicates whether or not the tree is empty.
   *
   * \return `true` if there are no AABBs stored in the tree; `false` otherwise.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto is_empty() const noexcept -> bool
  {
    return m_indexMap.empty();
  }

 private:
  using opt_index = std::optional<index_type>;

  std::map<key_type, index_type> m_indexMap;
  std::vector<aabb_node<key_type, T>> m_nodes;

  opt_index m_rootIndex{};
  opt_index m_nextFreeNodeIndex{};

  size_type m_allocatedNodes{};
  size_type m_nodeCapacity{24};
  size_type m_growthSize{m_nodeCapacity};

  void grow_pool()
  {
    assert(m_allocatedNodes == m_nodeCapacity);

    m_nodeCapacity += m_growthSize;
    m_nodes.resize(m_nodeCapacity);

    for (auto index = m_allocatedNodes; index < m_nodeCapacity; ++index) {
      auto& node = m_nodes.at(index);
      node.next = static_cast<index_type>(index + 1);
    }

    m_nodes.at(m_nodeCapacity - 1).next.reset();
    m_nextFreeNodeIndex = static_cast<index_type>(m_allocatedNodes);
  }

  [[nodiscard]] auto allocate_node() -> index_type
  {
    // if we have no free tree nodes then grow the pool
    if (!m_nextFreeNodeIndex) {
      grow_pool();
    }

    const auto index = m_nextFreeNodeIndex.value();
    const auto& node = m_nodes.at(index);
    m_nextFreeNodeIndex = node.next;
    ++m_allocatedNodes;

    return index;
  }

  void deallocate_node(index_type nodeIndex)
  {
    auto& node = m_nodes.at(nodeIndex);
    node.next = m_nextFreeNodeIndex;
    m_nextFreeNodeIndex = nodeIndex;
    --m_allocatedNodes;
  }

  void fix_upwards_tree(opt_index nodeIndex)
  {
    while (nodeIndex) {
      auto& node = m_nodes.at(nodeIndex.value());

      // every node should be a parent
      assert(node.left);
      assert(node.right);

      // fix height and area
      const auto& left = m_nodes.at(node.left.value());
      const auto& right = m_nodes.at(node.right.value());
      node.box = combine(left.box, right.box);

      nodeIndex = node.parent;
    }
  }

  [[nodiscard]] auto find_best_insertion_position(
      const node_type& leafNode) const -> index_type
  {
    auto treeNodeIndex = m_rootIndex.value();
    while (!m_nodes.at(treeNodeIndex).is_leaf()) {
      // because of the test in the while loop above we know we are never a leaf
      // inside it
      const auto& treeNode = m_nodes.at(treeNodeIndex);
      const auto leftNodeIndex = treeNode.left.value();
      const auto rightNodeIndex = treeNode.right.value();
      const auto& leftNode = m_nodes.at(leftNodeIndex);
      const auto& rightNode = m_nodes.at(rightNodeIndex);

      const auto combined = combine(treeNode.box, leafNode.box);

      const auto newParentNodeCost = 2.0f * combined.area();
      const auto minimumPushDownCost =
          2.0f * (combined.area() - treeNode.box.area());

      // use the costs to figure out whether to create a new parent here or
      // descend
      const auto costLeft =
          detail::get_left_cost(leftNode, leafNode, minimumPushDownCost);
      const auto costRight =
          detail::get_right_cost(rightNode, leafNode, minimumPushDownCost);

      // if the cost of creating a new parent node here is less than descending
      // in either direction then we know we need to create a new parent node
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

  void insert_leaf(index_type leafIndex)
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
    newParent.box = combine(leafNode.box, leafSibling.box);
    newParent.left = leafSiblingIndex;
    newParent.right = leafIndex;
    leafNode.parent = newParentIndex;
    leafSibling.parent = newParentIndex;

    if (!oldParentIndex) {
      // the old parent was the root and so this is now the root
      m_rootIndex = newParentIndex;
    } else {
      // the old parent was not the root and so we need to patch the left or
      // right index to point to the new node
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

  void remove_leaf(index_type leafIndex)
  {
    // if the leaf is the root then we can just clear the root pointer and
    // return
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
      // if we have a grand parent (i.e. the parent is not the root) then
      // destroy the parent and connect the sibling to the grandparent in its
      // place
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
      // if we have no grandparent then the parent is the root and so our
      // sibling becomes the root and has it's parent removed
      m_rootIndex = siblingNodeIndex;
      siblingNode.parent = std::nullopt;
      deallocate_node(parentNodeIndex);
    }

    leafNode.parent = std::nullopt;
  }

  void update_leaf(index_type leafIndex, const aabb_type& box)
  {
    auto& node = m_nodes.at(leafIndex);

    // if the node contains the new aabb then we just leave things
    if (node.box.contains(box)) {
      return;
    }

    remove_leaf(leafIndex);
    node.box = box;
    insert_leaf(leafIndex);
  }
};

}  // namespace abby

#endif  // ABBY__HEADER__GUARD_

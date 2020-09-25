#pragma once

#include <algorithm>  // min, max
#include <entt.hpp>
#include <forward_list>  // forward_list
#include <map>           // map
#include <optional>      // optional
#include <vector>        // vector

#include "vector2.hpp"

namespace wanderer {
inline namespace experimental {

struct aabb final
{
  vector2f min{};
  vector2f max{};
  float area{};
};

struct aabb_node final
{
  aabb box;
  entt::entity entity{entt::null};
  std::optional<int> parent{};
  std::optional<int> left{};
  std::optional<int> right{};
  std::optional<int> next{};
};

[[nodiscard]] inline auto is_leaf(const aabb_node& node) noexcept -> bool
{
  return !node.left;
}

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

  //  const auto centerX = result.min.x() + (width / 2.0f);
  //  const auto centerY = result.min.y() + (height / 2.0f);
  //  result.center = {centerX, centerY};

  return result;
}

[[nodiscard]] inline auto make_aabb(const vector2f& position,
                                    const vector2f& size) -> aabb
{
  aabb box;

  box.min = position;
  box.max.set_x(box.min.x() + size.x());
  box.max.set_y(box.min.y() + size.y());

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

}  // namespace experimental
}  // namespace wanderer

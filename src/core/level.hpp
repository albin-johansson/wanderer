#pragma once

#include <entt.hpp>

#include "aabb_tree.hpp"

namespace wanderer {

/**
 * @class level
 *
 * @brief Represents a tilemap level.
 *
 * @details Every level features its own registry and AABB tree.
 *
 * @headerfile level.hpp
 */
class level final
{
 public:
  level();

  void insert_aabb(entt::entity entity,
                   const vector2f& position,
                   const vector2f& size)
  {
    m_aabbTree.insert(entity, make_aabb(position, size));
  }

  void move_aabb(entt::entity entity, const vector2f& position)
  {
    const auto oldBox = get_aabb(entity);

    auto newBox = oldBox;
    newBox.min = position;
    newBox.max = position + (oldBox.max - oldBox.min);

    const auto width = newBox.max.x() - newBox.min.x();
    const auto height = newBox.max.y() - newBox.min.y();
    newBox.area = width * height;

    m_aabbTree.update(entity, newBox);
  }

  template <typename... Components>
  [[nodiscard]] decltype(auto) get(entt::entity entity)
  {
    return m_registry.get<Components...>(entity);
  }

  template <typename... Components>
  [[nodiscard]] decltype(auto) try_get(entt::entity entity)
  {
    return m_registry.try_get<Components...>(entity);
  }

  template <typename OutputIterator>
  void query_collisions(entt::entity id, OutputIterator iterator) const
  {
    return m_aabbTree.query_collisions(id, iterator);
  }

  [[nodiscard]] auto get_aabb(entt::entity entity) const -> const aabb&
  {
    return m_aabbTree.get_aabb(entity);
  }

  [[nodiscard]] auto registry() -> entt::registry&
  {
    return m_registry;
  }

 private:
  entt::registry m_registry;
  aabb_tree m_aabbTree;
};

}  // namespace wanderer

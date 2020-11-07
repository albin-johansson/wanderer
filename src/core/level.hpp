#pragma once

#include <entt.hpp>
#include <utility>  // forward

#include "abby.hpp"
#include "vector2.hpp"

namespace wanderer {

template <typename T>
[[nodiscard]] auto abby_vector(const basic_vector2<T>& vector) noexcept
    -> abby::vec2<T>
{
  return abby::vec2<T>{vector.x(), vector.y()};
}

/**
 * \class level
 *
 * \brief Represents a tilemap level.
 *
 * \details Every level features its own registry and AABB tree.
 *
 * \headerfile level.hpp
 */
class level final
{
 public:
  level();

  void insert_aabb(entt::entity entity,
                   const vector2f& position,
                   const vector2f& size)
  {
    m_aabbTree.emplace(entity, abby_vector(position), abby_vector(size));
  }

  void move_aabb(entt::entity entity, const vector2f& position)
  {
    m_aabbTree.relocate(entity, abby_vector(position));
  }

  template <typename... Components, typename T>
  void each(T&& lambda)
  {
    m_registry.view<Components...>().each(std::forward<T>(lambda));
  }

  [[nodiscard]] auto add_entity() -> entt::entity
  {
    return m_registry.create();
  }

  template <typename Component, typename... Args>
  decltype(auto) emplace(entt::entity entity, Args&&... args)
  {
    return m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
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

  /**
   * \copydoc aabb_tree::query_collisions()
   */
  template <typename OutputIterator>
  void query_collisions(entt::entity id, OutputIterator iterator) const
  {
    return m_aabbTree.query_collisions(id, iterator);
  }

  [[nodiscard, deprecated]] auto registry() -> entt::registry&
  {
    return m_registry;
  }

 private:
  entt::registry m_registry;
  abby::aabb_tree<entt::entity> m_aabbTree;
};

}  // namespace wanderer

#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>
#include <filesystem>  // path
#include <utility>     // forward

#include "abby.hpp"
#include "component/player.hpp"
#include "component/tilemap.hpp"
#include "component/tileset.hpp"
#include "component/viewport.hpp"
#include "delta.hpp"
#include "image_cache.hpp"
#include "null_entity.hpp"
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
  level(const std::filesystem::path& path,
        cen::renderer& renderer,
        image_cache& imageCache);

  void relocate_aabb(entt::entity entity, const vector2f& position)
  {
    m_aabbTree.relocate(entity, abby_vector(position));
  }

  template <typename... Components, typename T>
  void each(T&& lambda)
  {
    m_registry.view<Components...>().each(std::forward<T>(lambda));
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

  [[nodiscard]] auto row_count() const -> int
  {
    return m_registry.get<comp::tilemap>(m_tilemap.get()).rows;
  }

  [[nodiscard]] auto col_count() const -> int
  {
    return m_registry.get<comp::tilemap>(m_tilemap.get()).cols;
  }

  [[nodiscard]] auto player() const -> comp::player::entity
  {
    return m_player;
  }

  [[nodiscard]] auto viewport() const -> comp::viewport::entity
  {
    return m_viewport;
  }

  [[nodiscard]] auto tilemap() const -> comp::tilemap::entity
  {
    return m_tilemap;
  }

  [[nodiscard]] auto viewport_component() -> comp::viewport&
  {
    return m_registry.get<comp::viewport>(m_viewport.get());
  }

  [[nodiscard]] auto registry() -> entt::registry&
  {
    return m_registry;
  }

 private:
  entt::registry m_registry;
  abby::aabb_tree<entt::entity> m_aabbTree;
  comp::tilemap::entity m_tilemap{null<comp::tilemap>()};
  comp::tileset::entity m_tileset{null<comp::tileset>()};
  comp::viewport::entity m_viewport{null<comp::viewport>()};
  comp::player::entity m_player{null<comp::player>()};
};

}  // namespace wanderer

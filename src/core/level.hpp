#pragma once

#include <entt.hpp>
#include <utility>   // forward

#include "abby.hpp"
#include "component/player.hpp"
#include "component/render_bounds.hpp"
#include "component/spawnpoint.hpp"
#include "component/tilemap.hpp"
#include "component/tileset.hpp"
#include "component/viewport.hpp"
#include "delta.hpp"
#include "null_entity.hpp"
#include "render_bounds_system.hpp"
#include "vector2.hpp"
#include "maybe.hpp"

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
  friend class level_factory;

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

  template <typename OutputIterator>
  void query_collisions(entt::entity id, OutputIterator iterator) const
  {
    return m_aabbTree.query_collisions(id, iterator);
  }

  /**
   * \brief Returns the player entity associated with the level.
   *
   * \return the player entity.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto player() const -> comp::player::entity
  {
    return m_player;
  }

  /**
   * \brief Returns the viewport entity associated with the level.
   *
   * \return the viewport entity.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto viewport() const -> comp::viewport::entity
  {
    return m_viewport;
  }

  /**
   * \brief Returns the tilemap entity associated with the level.
   *
   * \return the tilemap entity.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto tilemap() const -> comp::tilemap::entity
  {
    return m_tilemap;
  }

  /**
   * \brief Returns the spawnpoint of the player in the level.
   *
   * \return the player spawnpoint.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto player_spawnpoint() const -> const vector2f&
  {
    return m_playerSpawnPosition.value();
  }

  /**
   * \brief Returns the viewport component associated with the level.
   *
   * \return the viewport component.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto viewport_component() -> comp::viewport&
  {
    return m_registry.get<comp::viewport>(m_viewport.get());
  }

  /**
   * \brief Returns the number of rows in the level tilemap.
   *
   * \return the amount of rows in the tilemap.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto row_count() const -> int
  {
    return m_registry.get<comp::tilemap>(m_tilemap.get()).rows;
  }

  /**
   * \brief Returns the number of columns in the level tilemap.
   *
   * \return the amount of columns in the tilemap.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto col_count() const -> int
  {
    return m_registry.get<comp::tilemap>(m_tilemap.get()).cols;
  }

  /**
   * \brief Returns the current render bounds of the level.
   *
   * \return the current render bounds.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto get_render_bounds() const -> comp::render_bounds
  {
    return sys::calculate_render_bounds(m_registry,
                                        m_viewport,
                                        row_count(),
                                        col_count());
  }

  /**
   * \brief Returns the registry associated with the level.
   *
   * \return the registry associated with the level.
   *
   * \since 0.1.0
   */
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
  maybe<vector2f> m_playerSpawnPosition;

  explicit level(entt::registry&& registry) : m_registry{std::move(registry)}
  {}
};

}  // namespace wanderer

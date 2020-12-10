#pragma once

#include <entt.hpp>
#include <utility>  // forward

#include "aabb_tree.hpp"
#include "abby.hpp"
#include "component/player.hpp"
#include "component/render_bounds.hpp"
#include "component/spawnpoint.hpp"
#include "component/tilemap.hpp"
#include "component/tileset.hpp"
#include "component/viewport.hpp"
#include "delta.hpp"
#include "maybe.hpp"
#include "null_entity.hpp"
#include "vector2.hpp"

namespace wanderer {

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

  using aabb_type = typename aabb_tree::aabb_type;

  void relocate_aabb(entt::entity entity, const vector2f& position);

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

  template <typename Component>
  [[nodiscard]] decltype(auto) get(entt::entity entity)
  {
    return m_registry.get<Component>(entity);
  }

  template <typename Component>
  [[nodiscard]] decltype(auto) try_get(entt::entity entity)
  {
    return m_registry.try_get<Component>(entity);
  }

  template <typename OutputIterator>
  void query_collisions(entt::entity id, OutputIterator iterator) const
  {
    return m_aabbTree.query(id, iterator);
  }

  [[nodiscard]] auto get_aabb(entt::entity id) const -> const aabb_type&;

  /**
   * \brief Returns the player entity associated with the level.
   *
   * \return the player entity.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto player() const -> comp::player::entity;

  /**
   * \brief Returns the viewport entity associated with the level.
   *
   * \return the viewport entity.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto viewport() const -> comp::viewport::entity;

  /**
   * \brief Returns the tilemap entity associated with the level.
   *
   * \return the tilemap entity.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto tilemap() const -> comp::tilemap::entity;

  /**
   * \brief Returns the spawnpoint of the player in the level.
   *
   * \return the player spawnpoint.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto player_spawnpoint() const -> const vector2f&;

  /**
   * \brief Returns the viewport component associated with the level.
   *
   * \return the viewport component.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto viewport_component() -> comp::viewport&;

  /**
   * \brief Returns the number of rows in the level tilemap.
   *
   * \return the amount of rows in the tilemap.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto row_count() const -> int;

  /**
   * \brief Returns the number of columns in the level tilemap.
   *
   * \return the amount of columns in the tilemap.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto col_count() const -> int;

  /**
   * \brief Returns the current render bounds of the level.
   *
   * \return the current render bounds.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto get_render_bounds() const -> comp::render_bounds;

  /**
   * \brief Returns the registry associated with the level.
   *
   * \return the registry associated with the level.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto registry() -> entt::registry&;

 private:
  entt::registry m_registry;
  aabb_tree m_aabbTree;
  comp::tilemap::entity m_tilemap{null<comp::tilemap>()};
  comp::tileset::entity m_tileset{null<comp::tileset>()};
  comp::viewport::entity m_viewport{null<comp::viewport>()};
  comp::player::entity m_player{null<comp::player>()};
  maybe<vector2f> m_playerSpawnPosition;

  explicit level(entt::registry&& registry);
};

}  // namespace wanderer

#pragma once

#include <entt.hpp>    // registry
#include <filesystem>  // path
#include <iterator>    // output_iterator
#include <utility>     // forward, move

#include "components/ctx/player.hpp"
#include "components/ctx/render_bounds.hpp"
#include "components/ctx/tileset.hpp"
#include "components/ctx/viewport.hpp"
#include "components/map/spawnpoint.hpp"
#include "components/map/tilemap.hpp"
#include "core/aliases/aabb_tree.hpp"
#include "core/aliases/delta_time.hpp"
#include "core/aliases/float2.hpp"
#include "core/aliases/map_id.hpp"
#include "core/aliases/maybe.hpp"
#include "core/ecs/null_entity.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/map/parse_ir.hpp"

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
  using aabb_type = typename aabb_tree::aabb_type;

  // Creates a level based on a parsed map file
  level(const ir::level& ordered, graphics_context& graphics);

  // Opens a level from a binary save file
  level(const std::filesystem::path& path, graphics_context& graphics);

  // Saves the level as a binary file
  void save(const std::filesystem::path& path) const;

  void relocate_aabb(entt::entity entity, float2 position);

  void update_render_bounds();

  template <typename... Components, typename T>
  void each(T&& lambda)
  {
    m_registry.view<Components...>().each(std::forward<T>(lambda));
  }

  template <typename Component>
  void clear()
  {
    m_registry.clear<Component>();
  }

  template <std::output_iterator<entt::entity> T>
  void query_collisions(const entt::entity id, T iterator) const
  {
    return m_tree.query(id, iterator);
  }

  template <typename Component, typename... Args>
  decltype(auto) emplace(const entt::entity entity, Args&&... args)
  {
    return m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
  }

  template <typename Component>
  [[nodiscard]] decltype(auto) get(const entt::entity entity)
  {
    return m_registry.get<Component>(entity);
  }

  template <typename Component>
  [[nodiscard]] decltype(auto) ctx()
  {
    return m_registry.ctx<Component>();
  }

  template <typename Component>
  [[nodiscard]] decltype(auto) try_get(const entt::entity entity)
  {
    return m_registry.try_get<Component>(entity);
  }

  [[nodiscard]] auto id() const noexcept -> map_id;

  [[nodiscard]] auto get_aabb(entt::entity id) const -> const aabb_type&;

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
  [[nodiscard]] auto player_spawnpoint() const -> float2;

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
   * \brief Returns the registry associated with the level.
   *
   * \return the registry associated with the level.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto registry() -> entt::registry&;

  [[nodiscard]] auto registry() const -> const entt::registry&;

 private:
  entt::registry m_registry;
  aabb_tree m_tree;
  comp::tilemap::entity m_tilemap{null<comp::tilemap>()};
  maybe<float2> m_playerSpawnPosition;

  void spawn_humanoids(const comp::tilemap& tilemap, graphics_context& graphics);
};

}  // namespace wanderer

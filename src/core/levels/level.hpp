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
  /**
   * \brief Creates a level based on a parsed tilemap file.
   *
   * \param data the parsed tilemap data.
   * \param graphics the graphics context used when loading textures.
   */
  level(const ir::level& data, graphics_context& graphics);

  /**
   * \brief Creates a level from a binary save file.
   *
   * \param path the file path of the binary save file.
   * \param graphics the graphics context used when loading textures.
   */
  level(const std::filesystem::path& path, graphics_context& graphics);

  /// \brief Saves the level as a binary save file.
  void save(const std::filesystem::path& path) const;

  /// Returns the unique ID associated with the level.
  [[nodiscard]] auto id() const noexcept -> map_id;

  /// Returns the tilemap entity associated with the level.
  [[nodiscard]] auto tilemap() const -> comp::tilemap::entity;

  /// Returns the spawnpoint of the player in the level.
  [[nodiscard]] auto player_spawnpoint() const -> float2;

  /// Returns the number of rows in the level tilemap.
  [[nodiscard]] auto row_count() const -> int;

  /// Returns the number of columns in the level tilemap.
  [[nodiscard]] auto col_count() const -> int;

  /// Returns the registry associated with the level.
  [[nodiscard]] auto registry() -> entt::registry&;

  /// \copydoc registry()
  [[nodiscard]] auto registry() const -> const entt::registry&;

  /// Returns the AABB tree used by the level.
  [[nodiscard]] auto tree() -> aabb_tree&;

 private:
  entt::registry m_registry;
  aabb_tree m_tree;
  comp::tilemap::entity m_tilemap{null<comp::tilemap>()};
  maybe<float2> m_playerSpawnPosition;

  void spawn_humanoids(const comp::tilemap& tilemap, graphics_context& graphics);
};

}  // namespace wanderer

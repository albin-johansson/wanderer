#include "level.hpp"

#include <fstream>  // ifstream, ofstream

#include "add_ground_layers.hpp"
#include "add_objects.hpp"
#include "add_tile_objects.hpp"
#include "components/humanoid_state.hpp"
#include "core/ecs/make_registry.hpp"
#include "core/serialization.hpp"
#include "core/utils/centurion_utils.hpp"
#include "make_tilemap.hpp"
#include "make_tileset.hpp"
#include "systems/graphics/depth_system.hpp"
#include "systems/graphics/drawable_system.hpp"
#include "systems/graphics/render_bounds_system.hpp"
#include "systems/graphics/viewport_system.hpp"
#include "systems/humanoid/humanoid_factory_system.hpp"
#include "systems/saves/saves_system.hpp"

namespace wanderer {

level::level(const ir::level& data, graphics_context& graphics)
    : m_registry{make_registry()}
    , m_tilemap{m_registry.create()}
    , m_playerSpawnPosition{data.playerSpawnPoint}
{
  m_tree.set_thickness_factor(std::nullopt);

  load_tileset_textures(data, graphics);
  auto& tileset = make_tileset(data.tilesets, m_registry, graphics);
  auto& tilemap = make_tilemap(data, m_registry, m_tilemap);

  m_registry.set<ctx::viewport>(sys::make_viewport(tilemap.size));

  add_ground_layers(m_registry, data);
  add_tile_objects(m_registry, m_tree, graphics, data, tileset);
  add_objects(m_registry, data);

  spawn_humanoids(tilemap, graphics);

  for (auto&& [entity, drawable] :
       m_registry.view<comp::depth_drawable, comp::humanoid>().each())
  {
    drawable.layer = tilemap.humanoidLayer;
  }

  sys::center_viewport_on(m_registry, player_spawnpoint());
  sys::update_drawables(m_registry);
  m_tree.rebuild();

  sys::update_depth(m_registry);
}

level::level(const std::filesystem::path& path, graphics_context& graphics)
{
  std::ifstream stream{path, std::ios::binary};
  input_archive archive{stream};

  m_registry = sys::restore_registry(archive);
  archive(m_tree);
  archive(m_tilemap);
  archive(m_playerSpawnPosition);
}

void level::save(const std::filesystem::path& path) const
{
  std::ofstream stream{path, std::ios::binary};
  output_archive archive{stream};

  sys::save_registry(m_registry, archive);
  archive(m_tree);
  archive(m_tilemap);
  archive(m_playerSpawnPosition);
}

void level::relocate_aabb(const entt::entity entity, const float2 position)
{
  m_tree.relocate(entity, position);
}

void level::update_render_bounds()
{
  sys::update_render_bounds(m_registry, row_count(), col_count());
}

auto level::id() const noexcept -> map_id
{
  return m_registry.get<comp::tilemap>(m_tilemap).id;
}

auto level::get_aabb(const entt::entity id) const -> const level::aabb_type&
{
  return m_tree.get_aabb(id);
}

auto level::tilemap() const -> comp::tilemap::entity
{
  return m_tilemap;
}

auto level::player_spawnpoint() const -> float2
{
  return m_playerSpawnPosition.value();
}

auto level::row_count() const -> int
{
  return m_registry.get<comp::tilemap>(m_tilemap).rows;
}

auto level::col_count() const -> int
{
  return m_registry.get<comp::tilemap>(m_tilemap).cols;
}

auto level::registry() -> entt::registry&
{
  return m_registry;
}

auto level::registry() const -> const entt::registry&
{
  return m_registry;
}

auto level::get_aabb_tree() -> aabb_tree&
{
  return m_tree;
}

void level::spawn_humanoids(const comp::tilemap& tilemap, graphics_context& graphics)
{
  // The player has to be created before other humanoids!
  m_registry.set<ctx::player>(
      sys::make_player(m_registry, m_tree, *m_playerSpawnPosition, graphics));

  for (auto&& [entity, spawnpoint] : m_registry.view<comp::spawnpoint>().each())
  {
    switch (spawnpoint.type)
    {
      case comp::spawnpoint_type::player:
        break;

      case comp::spawnpoint_type::skeleton: {
        sys::make_skeleton(m_registry, m_tree, spawnpoint.position, graphics);
        break;
      }
    }
  }
}

}  // namespace wanderer

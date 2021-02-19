#include "level.hpp"

#include <fstream>  // ifstream, ofstream

#include "add_ground_layers.hpp"
#include "add_objects.hpp"
#include "add_tile_objects.hpp"
#include "centurion_utils.hpp"
#include "create_tilemap.hpp"
#include "create_tileset.hpp"
#include "depth_drawables_system.hpp"
#include "humanoid_factory_system.hpp"
#include "make_registry.hpp"
#include "make_viewport.hpp"
#include "render_bounds_system.hpp"
#include "saves_system.hpp"
#include "serialization.hpp"
#include "viewport_system.hpp"

namespace wanderer {

level::level(const ir::level& data, graphics_context& graphics)
    : m_registry{make_registry()}
    , m_tilemap{m_registry.create()}
    , m_tileset{m_registry.create()}
    , m_playerSpawnPosition{data.playerSpawnPoint}
{
  m_tree.set_thickness_factor(std::nullopt);

  {
    // Load textures
    for (const auto& ts : data.tilesets) {
      const auto& textureData = ts.sheet;
      graphics.load_texture(textureData.id, textureData.path.c_str());
    }
  }

  auto& tileset = create_tileset(data.tilesets, m_registry, m_tileset);
  auto& tilemap = create_tilemap(data, m_registry, m_tilemap, m_tileset);

  each<comp::tile>([&](comp::tile& tile) {
    tile.sheet = graphics.get_texture(tile.texture);
  });

  m_viewport = sys::viewport::make_viewport(m_registry, tilemap.size);

  add_ground_layers(m_registry, data);
  add_tile_objects(m_registry, m_tree, data, tileset);
  add_objects(m_registry, data);

  each<comp::depth_drawable>([&](comp::depth_drawable& drawable) {
    drawable.texture = graphics.get_texture(drawable.textureId);
  });

  m_player =
      sys::add_player(m_registry, m_tree, *m_playerSpawnPosition, graphics);
  auto& drawable = m_registry.get<comp::depth_drawable>(m_player);
  drawable.layer = tilemap.humanoidLayer;

  sys::center_viewport_on(m_registry, m_viewport, player_spawnpoint());

  // This syncs the movable components with depth_drawable components
  sys::update_drawable_movables(m_registry);

  m_tree.rebuild();
}

level::level(const std::filesystem::path& path, graphics_context& graphics)
{
  std::ifstream stream{path, std::ios::binary};
  input_archive archive{stream};

  m_registry = sys::restore_registry(archive);
  archive(m_tree);
  archive(m_tilemap);
  archive(m_tileset);
  archive(m_viewport);
  archive(m_player);
  archive(m_playerSpawnPosition);
}

void level::save(const std::filesystem::path& path) const
{
  std::ofstream stream{path, std::ios::binary};
  output_archive archive{stream};

  sys::save_registry(m_registry, archive);
  archive(m_tree);
  archive(m_tilemap);
  archive(m_tileset);
  archive(m_viewport);
  archive(m_player);
  archive(m_playerSpawnPosition);
}

void level::relocate_aabb(const entt::entity entity, const vector2f& position)
{
  m_tree.relocate(entity, position);
}

auto level::id() const noexcept -> map_id
{
  return m_registry.get<comp::tilemap>(m_tilemap).id;
}

auto level::get_aabb(const entt::entity id) const -> const level::aabb_type&
{
  return m_tree.get_aabb(id);
}

auto level::player() const -> comp::player::entity
{
  return m_player;
}

auto level::viewport() const -> comp::viewport::entity
{
  return m_viewport;
}

auto level::tilemap() const -> comp::tilemap::entity
{
  return m_tilemap;
}

auto level::tileset() const -> comp::tileset::entity
{
  return m_tileset;
}

auto level::player_spawnpoint() const -> const vector2f&
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

auto level::get_render_bounds() const -> comp::render_bounds
{
  return sys::get_render_bounds(m_registry,
                                m_viewport,
                                row_count(),
                                col_count());
}

auto level::registry() -> entt::registry&
{
  return m_registry;
}

auto level::registry() const -> const entt::registry&
{
  return m_registry;
}

}  // namespace wanderer

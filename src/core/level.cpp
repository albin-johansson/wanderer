#include "level.hpp"

#include "humanoid_factory_system.hpp"
#include "make_map.hpp"
#include "make_registry.hpp"
#include "make_viewport_system.hpp"

namespace wanderer {

level::level(const std::filesystem::path& path,
             cen::renderer& renderer,
             image_cache& imageCache)
    : m_registry{make_registry()},
      m_tilemap{make_map(m_registry, path, renderer, imageCache)},
      m_viewport{sys::viewport::make_viewport(m_registry)}
{
  m_tileset = comp::tileset::entity{m_registry.view<comp::tileset>().front()};

  const auto& level = get<comp::tilemap>(m_tilemap.get());
  auto& viewport = viewport_component();
  viewport.levelSize.width = level.width;
  viewport.levelSize.height = level.height;

  each<comp::spawnpoint>([&](const comp::spawnpoint& spawnpoint) {
    load_spawnpoint(spawnpoint, renderer, imageCache);
  });
}

void level::load_spawnpoint(const comp::spawnpoint& spawnpoint,
                            cen::renderer& renderer,
                            image_cache& imageCache)
{
  switch (spawnpoint.type) {
    case comp::spawnpoint_type::player: {
      const auto id = sys::humanoid::add_player(m_registry,
                                                m_aabbTree,
                                                spawnpoint.position,
                                                renderer,
                                                imageCache);
      m_player = comp::player::entity{id};
      m_playerSpawnPosition = spawnpoint.position;
      break;
    }
    case comp::spawnpoint_type::skeleton: {
      sys::humanoid::add_skeleton(m_registry, m_aabbTree, renderer, imageCache);
      break;
    }
  }
}

}  // namespace wanderer

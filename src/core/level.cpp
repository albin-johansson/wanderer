#include "level.hpp"

#include "add_humanoid_state_dependencies.hpp"
#include "humanoid_factory_system.hpp"
#include "make_map.hpp"
#include "make_viewport_system.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_registry() -> entt::registry
{
  entt::registry registry;
  add_humanoid_state_dependencies(registry);
  return registry;
}

}  // namespace

level::level(const std::filesystem::path& path,
             cen::renderer& renderer,
             image_cache& imageCache)
    : m_registry{make_registry()},
      m_tilemap{make_map(m_registry, path, renderer, imageCache)},
      m_viewport{sys::viewport::make_viewport(m_registry)},
      m_player{sys::humanoid::add_player(m_registry,
                                         m_aabbTree,
                                         renderer,
                                         imageCache)}
{
  m_tileset = comp::tileset::entity{m_registry.view<comp::tileset>().front()};

  auto& view = get<comp::viewport>(m_viewport.get());
  auto& level = get<comp::tilemap>(m_tilemap.get());

  view.levelSize.width = level.width;
  view.levelSize.height = level.height;

  sys::humanoid::add_skeleton(m_registry, m_aabbTree, renderer, imageCache);
}

}  // namespace wanderer

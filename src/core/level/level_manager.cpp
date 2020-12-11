#include "level_manager.hpp"

#include <cassert>  // assert

#include "component/portal.hpp"
#include "level_factory.hpp"

namespace wanderer {

level_manager::level_manager(cen::renderer& renderer, texture_cache& cache)
{
  m_levels.reserve(5);

  auto world = level_factory::make("resource/map/world.json", renderer, cache);
  m_world = world->id();
  world->get<comp::viewport>(world->viewport()).keepInBounds = true;

  world->each<comp::portal>(
      [&, this](const entt::entity e, comp::portal& portal) {
        if (portal.target != m_world) {
          const auto path = "resource/map" / portal.path;
          auto level = level_factory::make(path, renderer, cache);
          m_levels.emplace(level->id(), std::move(level));
        }
      });

  m_levels.emplace(*m_world, std::move(world));
  m_current = m_world;
}

void level_manager::enable_world()
{
  m_current = m_world;
}

void level_manager::switch_to(const map_id id)
{
  assert(m_levels.count(id));
  m_current = id;
}

auto level_manager::current() noexcept -> level*
{
  assert(m_current);
  return m_levels.at(*m_current).get();
}

}  // namespace wanderer

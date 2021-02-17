#include "level_manager.hpp"

#include <cassert>  // assert
#include <utility>  // move

#include "parse_world.hpp"
#include "portal.hpp"

namespace wanderer {

level_manager::level_manager(graphics_context& graphics)
{
  m_levels.reserve(5);

  auto worldData = parse_world("resource/map/world.json");
  auto world = std::make_unique<level>(worldData.base, graphics);
  world->get<comp::viewport>(world->viewport()).keepInBounds = true;

  m_world = world->id();

  for (const auto& levelData : worldData.levels) {
    auto sublevel = std::make_unique<level>(levelData, graphics);
    const auto id = sublevel->id();
    m_levels.try_emplace(id, std::move(sublevel));
  }

  m_levels.try_emplace(*m_world, std::move(world));
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

auto level_manager::registry() -> entt::registry&
{
  return current()->registry();
}

auto level_manager::registry() const -> const entt::registry&
{
  return current()->registry();
}

auto level_manager::current() noexcept -> level*
{
  assert(m_current);
  return m_levels.at(*m_current).get();
}

auto level_manager::current() const noexcept -> const level*
{
  assert(m_current);
  return m_levels.at(*m_current).get();
}

auto level_manager::world() const -> map_id
{
  return m_world.value();
}

auto level_manager::current_id() const -> map_id
{
  return m_current.value();
}

}  // namespace wanderer

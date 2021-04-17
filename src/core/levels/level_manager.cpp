#include "level_manager.hpp"

#include <cassert>  // assert
#include <utility>  // move

#include "components/ctx/outside_level.hpp"
#include "components/graphics/level_switch_animation.hpp"
#include "components/map/portal.hpp"
#include "components/movable.hpp"
#include "core/resources.hpp"
#include "io/map/parse_world.hpp"
#include "systems/graphics/viewport_system.hpp"

namespace wanderer {

level_manager::level_manager(graphics_context& graphics)
{
  m_levels.reserve(5);

  auto worldData = parse_world(resources::map("world.json"));
  auto world = std::make_unique<level>(worldData.base, graphics);
  world->ctx<ctx::viewport>().keepInBounds = true;
  world->registry().set<ctx::outside_level>();

  m_world = world->id();

  for (const auto& levelData : worldData.levels)
  {
    auto sublevel = std::make_unique<level>(levelData, graphics);
    const auto id = sublevel->id();
    m_levels.try_emplace(id, std::move(sublevel));
  }

  m_levels.try_emplace(*m_world, std::move(world));
  m_current = m_world;
}

level_manager::level_manager(const save_file_info& info, graphics_context& graphics)
    : m_world{info.world}
    , m_current{info.current}
{
  m_levels.reserve(info.paths.size());
  for (const auto& [id, path] : info.paths)
  {
    m_levels.try_emplace(id, std::make_unique<level>(path, graphics));
  }
}

void level_manager::enable_world()
{
  m_current = m_world;
}

void level_manager::switch_to(const map_id id)
{
  {
    auto* currentLevel = current();
    auto& registry = currentLevel->registry();

    registry.clear<comp::level_switch_animation>();

    const auto player = currentLevel->ctx<ctx::player>().entity;
    auto& movable = currentLevel->get<comp::movable>(player);
    movable.velocity.zero();

    sys::center_viewport_on(registry, movable.position);
  }

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

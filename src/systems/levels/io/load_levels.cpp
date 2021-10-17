#include "load_levels.hpp"

#include "components/ctx/viewport.hpp"
#include "components/lvl/level.hpp"
#include "core/resources.hpp"
#include "io/tmx/parse_world.hpp"
#include "level_factory_system.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto CreateWorld(entt::registry& shared,
                               GraphicsContext& graphics,
                               const ir::world& data) -> entt::entity
{
  const auto entity = shared.create();

  auto& world = shared.emplace<comp::Level>(entity, MakeLevel(data.base, graphics));
  world.registry.ctx<ctx::Viewport>().keep_in_bounds = true;

  shared.emplace<comp::OutsideLevel>(entity);

  return entity;
}

}  // namespace

void LoadLevels(entt::registry& shared, GraphicsContext& graphics)
{
  CENTURION_LOG_INFO("Loading levels...");
  const auto data = io::parse_world(resources::map("main.json"));
  const auto world = CreateWorld(shared, graphics, data);

  for (const auto& sublevel : data.levels) {
    shared.emplace<comp::Level>(shared.create(), MakeLevel(sublevel, graphics));
  }

  shared.emplace<comp::ActiveLevel>(world);
}

}  // namespace wanderer::sys

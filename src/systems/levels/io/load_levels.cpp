#include "load_levels.hpp"

#include "components/ctx/viewport.hpp"
#include "components/lvl/level.hpp"
#include "components/lvl/outside_level.hpp"
#include "core/resources.hpp"
#include "io/parsing/parse_world.hpp"
#include "level_factory_system.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto create_world(entt::registry& shared,
                                graphics_context& graphics,
                                const ir::world& data) -> entt::entity
{
  const auto entity = shared.create();

  auto& world = shared.emplace<comp::level>(entity, make_level(data.base, graphics));
  world.registry.ctx<ctx::viewport>().keep_in_bounds = true;

  shared.emplace<comp::outside_level>(entity);

  return entity;
}

}  // namespace

void load_levels(entt::registry& shared, graphics_context& graphics)
{
  CENTURION_LOG_INFO("Loading levels...");
  const auto data = io::parse_world(resources::map("main.json"));
  const auto world = create_world(shared, graphics, data);

  for (const auto& sublevel : data.levels) {
    shared.emplace<comp::level>(shared.create(), make_level(sublevel, graphics));
  }

  shared.emplace<comp::active_level>(world);
}

}  // namespace wanderer::sys

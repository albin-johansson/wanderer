#include "load_game.hpp"

#include <cassert>  // assert

#include "components/map/level.hpp"
#include "components/outside_level.hpp"
#include "core/ecs/add_humanoid_state_dependencies.hpp"
#include "core/ecs/registry_utils.hpp"
#include "io/directories.hpp"
#include "io/saves/parse_save_file.hpp"
#include "systems/levels/level_factory_system.hpp"

namespace wanderer {

void load_game(entt::registry& shared,
               graphics_context& graphics,
               const std::string& name)
{
  const auto path = saves_directory() / name / (name + ".json");
  const auto contents = parse_save_file(path);

  shared.clear<comp::level>();
  shared.clear<comp::active_level>();

  for (const auto& data : contents.levels)
  {
    const auto entity = comp::level::entity{shared.create()};

    auto& level = shared.emplace<comp::level>(entity, sys::restore_level(data.path, graphics));
    level.id = data.id;

    if (level.id == contents.current)
    {
      shared.emplace<comp::active_level>(entity);
    }

    if (data.outside_level)
    {
      shared.emplace<comp::outside_level>(entity);
    }

    add_humanoid_state_dependencies(level.registry);
  }

  assert(shared.view<comp::active_level>().size() == 1);
}

}  // namespace wanderer

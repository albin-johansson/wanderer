#include "load_game.hpp"

#include <cassert>  // assert
#include <fstream>  // ifstream

#include "components/ctx/time_of_day.hpp"
#include "components/ctx/viewport.hpp"
#include "components/lvl/level.hpp"
#include "components/lvl/outside_level.hpp"
#include "core/serialization.hpp"
#include "io/directories.hpp"
#include "io/saves/parse_save_file.hpp"
#include "systems/levels/io/level_factory_system.hpp"

namespace wanderer {
namespace {

void restore_shared_data(const std::filesystem::path& path, entt::registry& shared)
{
  std::ifstream stream{path};
  input_archive archive{stream};

  shared.set<ctx::time_of_day>(restore<ctx::time_of_day>(archive));
}

}  // namespace

void load_game(entt::registry& shared,
               graphics_context& graphics,
               const std::string& name)
{
  const auto path = saves_directory() / name / (name + ".json");
  const auto contents = parse_save_file(path);

  shared.clear<comp::level>();
  shared.clear<comp::active_level>();
  restore_shared_data(saves_directory() / name / "shared_data.wanderer", shared);

  for (const auto& data : contents.levels) {
    const auto entity = comp::level::entity{shared.create()};

    auto& level =
        shared.emplace<comp::level>(entity, sys::restore_level(data.path, graphics));
    level.id = data.id;

    if (level.id == contents.current) {
      shared.emplace<comp::active_level>(entity);
    }

    if (data.outside_level) {
      shared.emplace<comp::outside_level>(entity);
    }

    auto& viewport = level.registry.ctx<ctx::viewport>();
    viewport.keep_in_bounds = data.keep_viewport_in_bounds;
  }

  assert(shared.view<comp::active_level>().size() == 1);
}

}  // namespace wanderer

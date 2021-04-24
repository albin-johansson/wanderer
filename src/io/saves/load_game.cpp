#include "load_game.hpp"

#include "io/directories.hpp"
#include "io/saves/parse_save_file.hpp"

namespace wanderer {

auto load_game(const std::string& name, graphics_context& graphics) -> level_manager
{
  const auto path = saves_directory() / name / (name + ".json");
  const auto contents = parse_save_file(path);
  return level_manager{contents, graphics};
}

}  // namespace wanderer

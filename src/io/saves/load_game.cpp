#include "load_game.hpp"

#include "files_directory.hpp"
#include "parse_save_file.hpp"

namespace wanderer {

auto load_game(const std::string& name, graphics_context& graphics) -> level_manager
{
  const auto path = files_directory() / "saves" / name / (name + ".json");
  const auto contents = parse_save_file(path);
  return level_manager{contents, graphics};
}

}  // namespace wanderer

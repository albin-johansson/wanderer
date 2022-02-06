#include "parse_levels.hpp"

#include <filesystem>  // path
#include <fstream>     // ifstream
#include <vector>      // vector

#include <yaml-cpp/yaml.h>

#include "wanderer/data/context/level.hpp"
#include "wanderer/io/directories.hpp"

namespace std_fs = std::filesystem;

namespace wanderer {
namespace {

[[nodiscard]] auto get_level_list() -> std::vector<std_fs::path>
{
  const auto path = std_fs::absolute("resources/maps/main.json");

  std::ifstream stream{path, std::ios::in};
  YAML::Parser parser{stream};

  std::vector<std_fs::path> levels;

  return levels;
}

}  // namespace

void parse_levels(entt::registry& shared)
{
  const auto path = std_fs::absolute("resources/maps/main.json");
  std::ifstream stream{path, std::ios::in};
  YAML::Parser parser{stream};

  //  const auto root = LoadLevel(shared, graphics, path);
  //  shared.emplace<ActiveLevel>(root);
  //
  //  auto& rootLevel = shared.get<Level>(root);
  //  rootLevel.registry.ctx<ctx::Viewport>().keep_in_bounds = true;
}

}  // namespace wanderer
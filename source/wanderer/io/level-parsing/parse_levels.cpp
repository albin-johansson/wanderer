#include "parse_levels.hpp"

#include <filesystem>  // path
#include <string>      // string
#include <vector>      // vector

#include <yaml-cpp/yaml.h>

#include "tiled-json/tiled_json_parser.hpp"
#include "wanderer/data/components/levels.hpp"
#include "wanderer/misc/exception.hpp"
#include "wanderer/misc/logging.hpp"

namespace wanderer {
namespace {

struct level_info final
{
  level_id id{};
  std::filesystem::path source;
};

[[nodiscard]] auto parse_level_paths() -> std::vector<level_info>
{
  std::vector<level_info> levels;

  const std::filesystem::path resources{"resources/maps"};
  const auto path = resources / "levels.yaml";

#if WANDERER_COMPILER_MSVC
  const auto root = YAML::LoadFile(path.string());
#else
  const auto root = YAML::LoadFile(path);
#endif  // WANDERER_COMPILER_MSVC

  if (auto sequence = root["levels"]) {
    levels.reserve(sequence.size());

    for (auto node : sequence) {
      const auto relativePath = node["source"].as<std::string>();
      auto& info = levels.emplace_back();
      info.id = node["id"].as<level_id>();
      info.source = resources / relativePath;
    }
  }

  if (levels.empty()) {
    throw_traced(WandererError{"Found no levels to load!"});
  }

  return levels;
}

}  // namespace

void parse_levels(entt::registry& shared, Graphics& graphics)
{
  const auto& cfg = shared.ctx().at<GameConfig>();
  auto& levels = shared.ctx().at<comp::Levels>();
  maybe<level_id> first;

  for (const auto& info : parse_level_paths()) {
    debug("Loading level '{}' from {}", info.id, info.source.string());

    if (levels.levels.contains(info.id)) {
      throw_traced(WandererError{"Detected duplicate level identifiers!"});
    }

    if (!first) {
      first = info.id;
    }

    const auto ext = info.source.extension();
    if (ext == ".json") {
      levels.levels[info.id] = io::parse_tiled_json_map(info.source, graphics, cfg);
    }
    // TODO
    // else if (ext == ".yaml") {
    //
    // }
    else {
      throw_traced(WandererError{"Unsupported map file extension!"});
    }
  }

  levels.current = first.value();
}

}  // namespace wanderer
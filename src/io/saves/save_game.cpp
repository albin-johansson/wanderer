#include "save_game.hpp"

#include <format>    // format
#include <fstream>   // ofstream
#include <iomanip>   // setw
#include <json.hpp>  // json
#include <string>    // string, to_string

#include "components/ctx/time_of_day.hpp"
#include "components/ctx/viewport.hpp"
#include "components/outside_level.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/serialization.hpp"
#include "io/directories.hpp"
#include "systems/levels/level_save_system.hpp"
#include "systems/levels/level_system.hpp"

using json_type = nlohmann::json;

namespace wanderer {
namespace {

inline constexpr int binary_data_version = 1;
inline constexpr int json_format_version = 1;

[[nodiscard]] auto unique_path(std::filesystem::path path) -> std::filesystem::path
{
  if (std::filesystem::exists(path))
  {
    const auto prefix = path.filename().string() + " ";
    for (auto index = 0; index < 100; ++index)  // Give up after 100 tries
    {
      auto newPath = path.parent_path() / (prefix + std::to_string(index + 1));
      if (!std::filesystem::exists(newPath))
      {
        return newPath;
      }
    }
  }

  return path;
}

void save_shared_registry(const std::filesystem::path& directory,
                          const entt::registry& shared)
{
  std::ofstream stream{directory / "shared_data.wanderer"};
  output_archive archive{stream};

  const auto& time = shared.ctx<ctx::time_of_day>();
  archive(time);
}

[[nodiscard]] auto save_levels(const entt::registry& shared,
                               const std::filesystem::path& directory) -> json_type
{
  auto levels = json_type::array();

  for (auto&& [entity, level] : shared.view<comp::level>().each())
  {
    const auto name = std::format("level_{}.wanderer", level.id.get());
    sys::save_level(level, directory / name);

    auto& object = levels.emplace_back();
    object["id"] = level.id.get();
    object["data"] = name;
    object["outside_level"] = shared.all_of<comp::outside_level>(entity);

    const auto& viewport = level.registry.ctx<ctx::viewport>();
    object["keep_viewport_in_bounds"] = viewport.keep_in_bounds;
  }

  return levels;
}

void save_common(const entt::registry& shared,
                 const std::string& name,
                 const std::filesystem::path& dir,
                 const cen::surface& snapshot)
{
  std::filesystem::create_directories(dir);
  snapshot.save_as_png(std::filesystem::absolute(dir / "snapshot.png").string());

  save_shared_registry(dir, shared);

  const auto& currentLevel = sys::current_level(shared);

  json_type json;
  json["name"] = name;
  json["json_format_version"] = json_format_version;
  json["data_format_version"] = binary_data_version;
  json["current_level"] = currentLevel.id.get();
  json["levels"] = save_levels(shared, dir);

  std::ofstream stream{dir / (name + ".json")};
  stream << std::setw(2) << json;
}

}  // namespace

void save_game(const std::string& name,
               const entt::registry& shared,
               const cen::surface& snapshot)
{
  const auto dir = unique_path(saves_directory() / name);
  const auto saveName = dir.filename().string();
  save_common(shared, saveName, dir, snapshot);
}

void create_exit_save(const entt::registry& shared, const cen::surface& snapshot)
{
  const std::string name{"exit_save"};
  save_common(shared, name, saves_directory() / name, snapshot);
}

}  // namespace wanderer

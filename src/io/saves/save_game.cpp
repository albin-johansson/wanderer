#include "save_game.hpp"

#include <fstream>   // ofstream
#include <iomanip>   // setw
#include <json.hpp>  // json
#include <string>    // string, to_string
#include <utility>   // move

#include "components/outside_level.hpp"
#include "io/directories.hpp"
#include "systems/levels/level_save_system.hpp"
#include "systems/levels/level_system.hpp"

using namespace std::string_literals;

using json_type = nlohmann::json;

namespace wanderer {
namespace {

inline constexpr int binary_data_version = 1;
inline constexpr int json_format_version = 1;

[[nodiscard]] auto unique_path(std::filesystem::path path) -> std::filesystem::path
{
  if (std::filesystem::exists(path))
  {
    for (auto index = 0; index < 100; ++index)  // Give up after 100 tries
    {
      const auto name = path.filename().string() + " " + std::to_string(index + 1);
      auto newPath = path.parent_path() / name;
      if (!std::filesystem::exists(newPath))
      {
        return newPath;
      }
    }
  }

  return path;
}

void save_common(const entt::registry& shared,
                 const std::string& name,
                 const std::filesystem::path& dir,
                 const cen::surface& snapshot)
{
  std::filesystem::create_directories(dir);
  snapshot.save_as_png(std::filesystem::absolute(dir / "snapshot.png").string());

  const auto& currentLevel = sys::current_level(shared);

  json_type json;

  json["name"] = name;
  json["json_format_version"] = json_format_version;
  json["data_format_version"] = binary_data_version;
  json["current_level"] = currentLevel.id.get();

  for (auto&& [entity, level] : shared.view<const comp::level>().each())
  {
    const auto levelName = "level_" + std::to_string(level.id.get()) + ".wanderer";
    sys::save(level, dir / levelName);

    json_type levelObject;

    levelObject["id"] = level.id.get();
    levelObject["data"] = levelName;
    levelObject["outside_level"] = shared.all_of<comp::outside_level>(entity);

    json["levels"].emplace_back(std::move(levelObject));
  }

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
  const auto name = "exit_save"s;
  save_common(shared, name, saves_directory() / name, snapshot);
}

}  // namespace wanderer

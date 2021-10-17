#include "save_game.hpp"

#include <fstream>  // ofstream
#include <iomanip>  // setw
#include <string>   // string, to_string

#include "components/ctx/time_of_day.hpp"
#include "core/ecs/registry_utils.hpp"
#include "io/directories.hpp"
#include "save_shared_registry.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto unique_path(std::filesystem::path path) -> std::filesystem::path
{
  if (std::filesystem::exists(path)) {
    const auto prefix = path.filename().string() + " ";
    for (auto index = 0; index < 100; ++index)  // Give up after 100 tries
    {
      auto newPath = path.parent_path() / (prefix + std::to_string(index + 1));
      if (!std::filesystem::exists(newPath)) {
        return newPath;
      }
    }
  }

  return path;
}

void save_common(const entt::registry& shared,
                 const std::filesystem::path& dir,
                 const cen::surface& snapshot)
{
  std::filesystem::create_directories(dir);
  snapshot.save_as_png(std::filesystem::absolute(dir / "snapshot.png").string());
  save_shared_registry(shared, dir / "data.wanderer");
}

}  // namespace

void save_game(const std::string& name,
               const entt::registry& shared,
               const cen::surface& snapshot)
{
  const auto dir = unique_path(GetSavesDirectory() / name);
  save_common(shared, dir, snapshot);
}

void create_exit_save(const entt::registry& shared, const cen::surface& snapshot)
{
  save_common(shared, GetSavesDirectory() / "exit_save", snapshot);
}

}  // namespace wanderer

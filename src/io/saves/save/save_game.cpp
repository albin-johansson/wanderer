#include "save_game.hpp"

#include <fstream>  // ofstream
#include <iomanip>  // setw
#include <string>   // string, to_string

#include "components/time_of_day.hpp"
#include "core/ecs/registry_utils.hpp"
#include "io/directories.hpp"
#include "save_shared_registry.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto ToUniquePath(std::filesystem::path path) -> std::filesystem::path
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

void SaveCommon(const entt::registry& shared,
                const std::filesystem::path& dir,
                const cen::surface& snapshot)
{
  std::filesystem::create_directories(dir);
  snapshot.save_as_png(std::filesystem::absolute(dir / "snapshot.png").string());
  SaveSharedRegistry(shared, dir / "data.wanderer");
}

}  // namespace

void SaveGame(const std::string& name,
              const entt::registry& shared,
              const cen::surface& snapshot)
{
  const auto dir = ToUniquePath(GetSavesDirectory() / name);
  SaveCommon(shared, dir, snapshot);
}

void CreateExitSave(const entt::registry& shared, const cen::surface& snapshot)
{
  SaveCommon(shared, GetSavesDirectory() / "exit_save", snapshot);
}

}  // namespace wanderer

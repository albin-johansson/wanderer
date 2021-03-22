#include "settings_system.hpp"

#include <filesystem>  // path, exists, copy
#include <fstream>     // ifstream

#include "files_directory.hpp"
#include "ini.hpp"
#include "settings.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto default_settings() noexcept -> comp::settings
{
  comp::settings settings;

  settings.resolution = cen::screen::size();
  settings.fullscreen = true;
  settings.integerScaling = true;

  return settings;
}

[[nodiscard]] auto read_settings(const std::filesystem::path& path,
                                 const comp::settings& defaults)
    -> comp::settings
{
  std::ifstream stream{path};
  const ini_file file{stream};

  comp::settings settings;

  settings.integerScaling = file.get<bool>("Graphics", "UseIntegerScaling")
                                .value_or(defaults.integerScaling);

  return settings;
}

}  // namespace

void load_settings(entt::registry& registry)
try
{
  const auto path = files_directory() / "settings.ini";
  const auto defaults = default_settings();

  if (std::filesystem::exists(path))
  {
    registry.set<comp::settings>(read_settings(path, defaults));
  }
  else
  {
    std::filesystem::copy("resources/settings.ini", path);
    registry.set<comp::settings>(defaults);
  }
} catch (...)
{
  cen::log::error("Failed to load settings!");
}

}  // namespace wanderer::sys

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

  CENTURION_LOG_INFO("Reading settings: \"%s\"", path.string().c_str());

  comp::settings settings;

  settings.fullscreen =
      file.get<bool>("Graphics", "Fullscreen").value_or(defaults.fullscreen);
  settings.integerScaling = file.get<bool>("Graphics", "UseIntegerScaling")
                                .value_or(defaults.integerScaling);

  if constexpr (cen::is_debug_build())
  {
    cen::log::info("Read settings...");
    cen::log::info("  [BOOL] fullscreen = %i", settings.fullscreen);
    cen::log::info("  [BOOL] integerScaling = %i", settings.integerScaling);
  }

  return settings;
}

}  // namespace

void load_settings(entt::registry& registry)
{
  const auto path = files_directory() / "settings.ini";
  const auto defaults = default_settings();

  if (std::filesystem::exists(path))
  {
    registry.set<comp::settings>(read_settings(path, defaults));
  }
  else
  {
    CENTURION_LOG_INFO("Copying default settings to preferred path...");
    std::filesystem::copy("resources/settings.ini", path);
    registry.set<comp::settings>(defaults);
  }
}

void save_settings_before_exit(const entt::registry& registry)
{
  const auto path = files_directory() / "settings.ini";
  const auto& settings = registry.ctx<comp::settings>();

  std::ofstream stream{path};
  stream << "[Graphics]\n";
  stream << "Fullscreen=" << (settings.fullscreen ? "true" : "false") << '\n';
  stream << "UseIntegerScaling="
         << (settings.integerScaling ? "true" : "false");

  if constexpr (cen::is_debug_build())
  {
    cen::log::info("Saving settings...");
    cen::log::info("  [BOOL] fullscreen = %i", settings.fullscreen);
    cen::log::info("  [BOOL] integerScaling = %i", settings.integerScaling);
  }
}

}  // namespace wanderer::sys

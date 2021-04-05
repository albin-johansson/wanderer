#include "settings_system.hpp"

#include <filesystem>  // path, exists, copy
#include <fstream>     // ifstream

#include "files_directory.hpp"
#include "ini.hpp"
#include "settings.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto default_settings() noexcept -> ctx::settings
{
  ctx::settings settings;

  settings.fullscreen = true;
  settings.integerScaling = true;
  settings.simulateLights = true;

  return settings;
}

void log_settings(const ctx::settings& settings)
{
  cen::log::info("  [BOOL] fullscreen = %i", settings.fullscreen);
  cen::log::info("  [BOOL] integerScaling = %i", settings.integerScaling);
  cen::log::info("  [BOOL] simulateLights = %i", settings.simulateLights);
}

[[nodiscard]] auto read_settings(const std::filesystem::path& path,
                                 const ctx::settings& defaults) -> ctx::settings
{
  std::ifstream stream{path};
  const ini_file file{stream};

  CENTURION_LOG_INFO("Reading settings: \"%s\"", path.string().c_str());

  ctx::settings settings{};

  // clang-format off
  settings.fullscreen = file.get<bool>("Graphics", "Fullscreen").value_or(defaults.fullscreen);
  settings.integerScaling = file.get<bool>("Graphics", "UseIntegerScaling").value_or(defaults.integerScaling);
  settings.simulateLights = file.get<bool>("Graphics", "SimulateLights").value_or(defaults.simulateLights);
  // clang-format on

  if constexpr (cen::is_debug_build())
  {
    cen::log::info("Read settings...");
    log_settings(settings);
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
    registry.set<ctx::settings>(read_settings(path, defaults));
  }
  else
  {
    CENTURION_LOG_INFO("Copying default settings to preferred path...");
    std::filesystem::copy("resources/settings.ini", path);
    registry.set<ctx::settings>(defaults);
  }
}

void save_settings_before_exit(const entt::registry& registry)
{
  const auto path = files_directory() / "settings.ini";
  const auto& settings = registry.ctx<ctx::settings>();

  const auto toString = [](const bool value) {
    return value ? "true" : "false";
  };

  std::ofstream stream{path};
  stream << "[Graphics]\n";

  stream << "Fullscreen=" << toString(settings.fullscreen) << '\n';
  stream << "UseIntegerScaling=" << toString(settings.integerScaling) << '\n';
  stream << "SimulateLights=" << toString(settings.simulateLights);

  if constexpr (cen::is_debug_build())
  {
    cen::log::info("Saving settings...");
    log_settings(settings);
  }
}

}  // namespace wanderer::sys

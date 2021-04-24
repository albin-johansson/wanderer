#include "settings_system.hpp"

#include <centurion.hpp>  // ...
#include <filesystem>     // path, exists, copy
#include <fstream>        // ifstream

#include "components/ctx/settings.hpp"
#include "io/directories.hpp"
#include "io/ini.hpp"

namespace wanderer::sys {
namespace {

inline const auto settings_file = files_directory() / "settings.ini";

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
  cen::log::info("  [bool] fullscreen = %i", settings.fullscreen);
  cen::log::info("  [bool] integerScaling = %i", settings.integerScaling);
  cen::log::info("  [bool] simulateLights = %i", settings.simulateLights);
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
  const auto defaults = default_settings();

  if (std::filesystem::exists(settings_file))
  {
    registry.set<ctx::settings>(read_settings(settings_file, defaults));
  }
  else
  {
    CENTURION_LOG_INFO("Copying default settings to preferred path...");
    std::filesystem::copy("resources/settings.ini", settings_file);
    registry.set<ctx::settings>(defaults);
  }
}

auto toggle_fullscreen(entt::registry& registry) -> bool
{
  auto& settings = registry.ctx<ctx::settings>();
  settings.fullscreen = !settings.fullscreen;
  return settings.fullscreen;
}

auto toggle_integer_scaling(entt::registry& registry) -> bool
{
  auto& settings = registry.ctx<ctx::settings>();
  settings.integerScaling = !settings.integerScaling;
  return settings.integerScaling;
}

auto toggle_simulate_lights(entt::registry& registry) -> bool
{
  auto& settings = registry.ctx<ctx::settings>();
  settings.simulateLights = !settings.simulateLights;
  return settings.simulateLights;
}

void save_settings_before_exit(const entt::registry& registry)
{
  const auto& settings = registry.ctx<const ctx::settings>();

  const auto toString = [](const bool value) {
    return value ? "true" : "false";
  };

  std::ofstream stream{settings_file};
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

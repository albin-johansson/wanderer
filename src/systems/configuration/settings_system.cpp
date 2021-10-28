#include "settings_system.hpp"

#include <filesystem>  // path, exists, copy

#include <centurion.hpp>  // log, is_debug_build
#include <init/ini.hpp>   // ini, read_ini, write_ini

#include "components/settings.hpp"
#include "io/directories.hpp"

namespace wanderer::sys {
namespace {

inline const auto settings_file = GetFilesDirectory() / "settings.ini";

[[nodiscard]] constexpr auto GetDefaultSettings() noexcept -> ctx::Settings
{
  ctx::Settings settings;

  settings.fullscreen = true;
  settings.integer_scaling = true;

  return settings;
}

void LogSettings(const ctx::Settings& settings)
{
  cen::log::info("  [bool] fullscreen = %i", settings.fullscreen);
  cen::log::info("  [bool] integerScaling = %i", settings.integer_scaling);
}

[[nodiscard]] auto ReadSettings(const std::filesystem::path& path) -> ctx::Settings
{
  CENTURION_LOG_INFO("Reading settings: \"%s\"", path.string().c_str());

  const auto ini = init::read_ini(path);
  auto settings = GetDefaultSettings();

  const auto& graphics = ini.at("Graphics");
  graphics.at("Fullscreen").get_to(settings.fullscreen);
  graphics.at("UseIntegerScaling").get_to(settings.integer_scaling);

  if constexpr (cen::is_debug_build()) {
    cen::log::info("Finished reading settings...");
    LogSettings(settings);
  }

  return settings;
}

}  // namespace

void LoadSettings(entt::registry& registry)
{
  if (std::filesystem::exists(settings_file)) {
    registry.set<ctx::Settings>(ReadSettings(settings_file));
  }
  else {
    CENTURION_LOG_INFO("Copying default settings to preferred path...");
    std::filesystem::copy("resources/settings.ini", settings_file);
    registry.set<ctx::Settings>(GetDefaultSettings());
  }
}

auto ToggleFullscreen(entt::registry& registry) -> bool
{
  auto& settings = registry.ctx<ctx::Settings>();
  settings.fullscreen = !settings.fullscreen;
  return settings.fullscreen;
}

auto ToggleIntegerScaling(entt::registry& registry) -> bool
{
  auto& settings = registry.ctx<ctx::Settings>();
  settings.integer_scaling = !settings.integer_scaling;
  return settings.integer_scaling;
}

void SaveSettingsBeforeExit(const entt::registry& registry)
{
  const auto& settings = registry.ctx<ctx::Settings>();

  init::ini ini;
  ini["Graphics"]["Fullscreen"] = settings.fullscreen;
  ini["Graphics"]["UseIntegerScaling"] = settings.integer_scaling;

  init::write_ini(ini, settings_file);

  if constexpr (cen::is_debug_build()) {
    cen::log::info("Saving settings...");
    LogSettings(settings);
  }
}

}  // namespace wanderer::sys

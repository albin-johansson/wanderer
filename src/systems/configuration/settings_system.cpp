#include "settings_system.hpp"

#include <centurion.hpp>        // ...
#include <filesystem>           // path, exists, copy
#include <rune/everything.hpp>  // ini_file

#include "components/ctx/settings.hpp"
#include "io/directories.hpp"

namespace wanderer::sys {
namespace {

inline const auto settings_file = files_directory() / "settings.ini";

[[nodiscard]] constexpr auto default_settings() noexcept -> ctx::settings
{
  ctx::settings settings;

  settings.fullscreen = true;
  settings.integer_scaling = true;

  return settings;
}

void log_settings(const ctx::settings& settings)
{
  cen::log::info("  [bool] fullscreen = %i", settings.fullscreen);
  cen::log::info("  [bool] integerScaling = %i", settings.integer_scaling);
}

[[nodiscard]] auto read_settings(const std::filesystem::path& path) -> ctx::settings
{
  CENTURION_LOG_INFO("Reading settings: \"%s\"", path.string().c_str());

  const auto ini = rune::read_ini(path).value();
  auto settings = default_settings();

  const auto& graphics = ini.at("Graphics");
  graphics.at("Fullscreen").get_to(settings.fullscreen);
  graphics.at("UseIntegerScaling").get_to(settings.integer_scaling);

  if constexpr (cen::is_debug_build())
  {
    cen::log::info("Finished reading settings...");
    log_settings(settings);
  }

  return settings;
}

}  // namespace

void load_settings(entt::registry& registry)
{
  if (std::filesystem::exists(settings_file))
  {
    registry.set<ctx::settings>(read_settings(settings_file));
  }
  else
  {
    CENTURION_LOG_INFO("Copying default settings to preferred path...");
    std::filesystem::copy("resources/settings.ini", settings_file);
    registry.set<ctx::settings>(default_settings());
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
  settings.integer_scaling = !settings.integer_scaling;
  return settings.integer_scaling;
}

void save_settings_before_exit(const entt::registry& registry)
{
  const auto& settings = registry.ctx<ctx::settings>();

  rune::ini_file ini;
  ini["Graphics"]["Fullscreen"] = settings.fullscreen;
  ini["Graphics"]["UseIntegerScaling"] = settings.integer_scaling;

  rune::write_ini(ini, settings_file);

  if constexpr (cen::is_debug_build())
  {
    cen::log::info("Saving settings...");
    log_settings(settings);
  }
}

}  // namespace wanderer::sys

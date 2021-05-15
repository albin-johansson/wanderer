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

  std::ifstream stream{path};
  const ini_file file{stream};

  auto settings = default_settings();
  settings.fullscreen =
      file.get<bool>("Graphics", "Fullscreen").value_or(settings.fullscreen);
  settings.integer_scaling =
      file.get<bool>("Graphics", "UseIntegerScaling").value_or(settings.integer_scaling);

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
  const auto& settings = registry.ctx<const ctx::settings>();

  const auto stringify = [](const bool value) {
    return value ? "true" : "false";
  };

  std::ofstream stream{settings_file};
  stream << "[Graphics]\n";
  stream << "Fullscreen=" << stringify(settings.fullscreen) << '\n';
  stream << "UseIntegerScaling=" << stringify(settings.integer_scaling) << '\n';

  if constexpr (cen::is_debug_build())
  {
    cen::log::info("Saving settings...");
    log_settings(settings);
  }
}

}  // namespace wanderer::sys

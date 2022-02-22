#include "settings.hpp"

#include <filesystem>  // exists
#include <fstream>     // ifstream, ofstream
#include <ios>         // ios

#include "directories.hpp"
#include "settings.pb.h"
#include "wanderer/misc/logging.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto _default_settings() -> settings
{
  settings s;

  s.flags = settings::fullscreen_bit | settings::vsync_bit;

  return s;
}

[[nodiscard]] auto _settings_file_path() -> const std::filesystem::path&
{
  static const auto path = get_persistent_file_dir() / "settings.bin";
  return path;
}

}  // namespace

void settings::set_flag(const uint64 flag, const bool value) noexcept
{
  if (value) {
    flags |= flag;
  }
  else {
    flags &= ~flag;
  }
}

auto settings::test_flag(const uint64 flag) const noexcept -> bool
{
  return flags & flag;
}

auto load_settings() -> settings
{
  const auto& path = _settings_file_path();
  debug("Loading settings from {}", path);

  if (std::filesystem::exists(path)) {
    std::ifstream stream{path, std::ios::binary | std::ios::in};

    proto::settings in;
    if (in.ParseFromIstream(&stream)) {
      settings result = _default_settings();

      if (in.has_fullscreen()) {
        result.set_flag(settings::fullscreen_bit, in.fullscreen());
      }

      if (in.has_vsync()) {
        result.set_flag(settings::vsync_bit, in.vsync());
      }

      info("[OPTION] fullscreen = '{}'", result.test_flag(settings::fullscreen_bit));
      info("[OPTION] vsync = '{}'", result.test_flag(settings::vsync_bit));

      return result;
    }
    else {
      warn("Failed to parse persistent settings, assuming defaults...");
      return _default_settings();
    }
  }
  else {
    info("Found no persistent settings file, assuming defaults...");
    return _default_settings();
  }
}

void save_settings(const settings& s)
{
  proto::settings out;
  out.set_fullscreen(s.test_flag(settings::fullscreen_bit));
  out.set_vsync(s.test_flag(settings::vsync_bit));

  const auto& path = _settings_file_path();
  debug("Saving settings to {}", path);

  std::ofstream stream{path, std::ios::binary | std::ios::out | std::ios::trunc};

  out.SerializeToOstream(&stream);
}

}  // namespace wanderer
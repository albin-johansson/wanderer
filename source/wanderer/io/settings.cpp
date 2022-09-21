#include "settings.hpp"

#include <filesystem>  // exists
#include <fstream>     // ifstream, ofstream
#include <ios>         // ios

#include "directories.hpp"
#include "settings.pb.h"
#include "wanderer/misc/logging.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto _default_settings() -> Settings
{
  Settings s;

  s.flags = Settings::fullscreen_bit | Settings::vsync_bit;

  return s;
}

[[nodiscard]] auto _settings_file_path() -> const std::filesystem::path&
{
  static const auto path = get_persistent_file_dir() / "settings.bin";
  return path;
}

}  // namespace

void Settings::set_flag(const uint64 flag, const bool value) noexcept
{
  if (value) {
    flags |= flag;
  }
  else {
    flags &= ~flag;
  }
}

auto Settings::test_flag(const uint64 flag) const noexcept -> bool
{
  return flags & flag;
}

auto load_settings() -> Settings
{
  const auto& path = _settings_file_path();
  debug("Loading settings from {}", path.string());

  if (std::filesystem::exists(path)) {
    std::ifstream stream{path, std::ios::binary | std::ios::in};

    proto::settings in;
    if (in.ParseFromIstream(&stream)) {
      Settings result = _default_settings();

      if (in.has_fullscreen()) {
        result.set_flag(Settings::fullscreen_bit, in.fullscreen());
      }

      if (in.has_vsync()) {
        result.set_flag(Settings::vsync_bit, in.vsync());
      }

      if (in.has_integer_scaling()) {
        result.set_flag(Settings::integer_scaling_bit, in.integer_scaling());
      }

      info("[OPTION] fullscreen = '{}'", result.test_flag(Settings::fullscreen_bit));
      info("[OPTION] vsync = '{}'", result.test_flag(Settings::vsync_bit));
      info("[OPTION] integer scaling = '{}'",
           result.test_flag(Settings::integer_scaling_bit));

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

void save_settings(const Settings& s)
{
  proto::settings out;
  out.set_fullscreen(s.test_flag(Settings::fullscreen_bit));
  out.set_vsync(s.test_flag(Settings::vsync_bit));
  out.set_integer_scaling(s.test_flag(Settings::integer_scaling_bit));

  const auto& path = _settings_file_path();
  debug("Saving settings to {}", path.string());

  std::ofstream stream{path, std::ios::binary | std::ios::out | std::ios::trunc};

  out.SerializeToOstream(&stream);
}

}  // namespace wanderer
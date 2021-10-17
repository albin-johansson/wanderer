#include "rune_configuration.hpp"

#include <centurion.hpp>        // renderer
#include <filesystem>           // exists
#include <rune/everything.hpp>  // get_cfg, save_configuration, load_configuration

#include "core/game_constants.hpp"
#include "directories.hpp"

namespace wanderer {
namespace {

inline const auto file = GetFilesDirectory() / "rune.ini";

void save_default_configuration()
{
  auto& cfg = rune::get_cfg();
  cfg.window_title = "Wanderer";
  cfg.logical_size = glob::logical_size<>;
  cfg.renderer_flags = cen::renderer::accelerated | cen::renderer::target_textures;
  cfg.engine_max_tick_rate = 240;

  rune::save_configuration(file);
}

}  // namespace

void PrepareRuneConfiguration()
{
  if (std::filesystem::exists(file)) {
    rune::load_configuration(file);
  }
  else {
    save_default_configuration();
  }
}

}  // namespace wanderer

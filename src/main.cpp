#include <centurion.hpp>        // library
#include <rune/everything.hpp>  // get_cfg

#include "core/game_constants.hpp"
#include "wanderer_engine.hpp"

auto main(int, char**) -> int
{
  cen::library centurion;
  cen::log::use_preset_output_function();

  if constexpr (cen::is_debug_build())
  {
    cen::log::set_priority(cen::log_priority::debug);
  }

  auto& cfg = rune::get_cfg();
  cfg.window_title = "Wanderer";
  cfg.logical_size = wanderer::glob::logical_size<>;
  cfg.renderer_flags = cen::renderer::accelerated | cen::renderer::target_textures;
  cfg.engine_max_tick_rate = 240;

  wanderer::wanderer_engine engine;
  return engine.run();
}
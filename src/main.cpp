#include <centurion.hpp>  // library, is_debug_build, use_preset_output_function, ...

#include "io/rune_configuration.hpp"
#include "wanderer_engine.hpp"

auto main(int, char**) -> int
{
  cen::library centurion;
  cen::log::use_preset_output_function();

  if constexpr (cen::is_debug_build()) {
    cen::log::set_priority(cen::log_priority::debug);
  }

  wanderer::prepare_rune_configuration();

  wanderer::wanderer_engine engine;
  return engine.run();
}
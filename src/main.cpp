// clang-format off
#define RUNE_TEXTURE_ID_UNDERLYING_TYPE entt::id_type
// clang-format on

#include <SDL.h>

#include <centurion.hpp>  // library
#include <entt.hpp>       // id_type
#include <rune.hpp>       // ...

#include "wanderer_engine.hpp"

auto main(int, char**) -> int
{
  cen::library centurion;
  cen::log::use_preset_output_function();

  if constexpr (cen::is_debug_build())
  {
    cen::log::set_priority(cen::log_priority::debug);
  }

  wanderer::wanderer_engine engine;
  return engine.run();
}
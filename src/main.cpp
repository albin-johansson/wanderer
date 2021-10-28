#include <centurion.hpp>

#include "game.hpp"

auto main(int, char**) -> int
{
  cen::library centurion;
  cen::log::use_preset_output_function();

  if constexpr (cen::is_debug_build()) {
    cen::log::set_priority(cen::log_priority::debug);
  }

  wanderer::Game game;
  return game.Run();
}
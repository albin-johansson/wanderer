#include <centurion.hpp>

#include "wanderer_engine.hpp"

auto main(int, char**) -> int
{
  cen::library centurion;
  cen::log::set_priority(cen::log_priority::info);

  wanderer::wanderer_engine engine;
  return engine.run();
}
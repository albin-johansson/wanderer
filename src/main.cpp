#include <centurion.hpp>

#include "wanderer_engine.hpp"

auto main(int, char**) -> int
{
  cen::library centurion;
  wanderer::wanderer_engine engine;
  return engine.run();
}
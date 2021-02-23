#include <cen/centurion.hpp>
#include <cen/log.hpp>

#include "wanderer_engine.hpp"

int main(int, char**)
{
  cen::library lib;
  cen::log::set_priority(cen::log::priority::info);

  wanderer::wanderer_engine engine;
  return engine.run();
}
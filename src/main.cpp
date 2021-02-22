#include <cen/centurion.hpp>
#include <cen/log.hpp>

#include "wanderer_engine.hpp"

using namespace wanderer;

int main(int, char**)
{
  cen::library lib;

  cen::log::set_priority(cen::log::priority::info);

  wanderer_engine app;
  return app.run();
}
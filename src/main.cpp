#include <cen/centurion.hpp>
#include <cen/log.hpp>

#include "wanderer_app.hpp"

using namespace wanderer;

int main(int, char**)
{
  cen::library lib;

  cen::log::set_priority(cen::log::priority::info);

  wanderer_app app;
  return app.run();
}
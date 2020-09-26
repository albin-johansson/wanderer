#include <cen/centurion.hpp>
#include <cen/log.hpp>

#include "application.hpp"

using namespace wanderer;

int main(int, char**)
{
  cen::library lib;

  cen::log::set_priority(cen::log::priority::info);

  application app;
  app.run();

  return 0;
}
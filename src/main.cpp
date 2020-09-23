#ifdef NDEBUG
#define BOOST_DISABLE_ASSERTS
#endif

#include <centurion.hpp>
#include <font.hpp>
#include <log.hpp>
#include <surface.hpp>

#include "application.h"
#include "random_utils.h"

using namespace wanderer;

int main(int, char**)
{
  math::init_rnd();
  cen::library lib;

  cen::log::set_priority(cen::log::priority::info);

  application app;
  app.run();
  return 0;
}
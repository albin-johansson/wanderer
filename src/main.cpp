#include <centurion.h>
#include <hints.h>

#include "application.h"
#include "random_utils.h"

using centurion::Centurion;
using centurion::Log;

using namespace wanderer;

int main(int, char**)
{
  math::init_rnd();

  Centurion c;

  using namespace centurion::hint;
  set_hint<RenderDriver>(RenderDriver::OpenGL);

  Log::set_priority(Log::Priority::Info);
  run();
  return 0;
}
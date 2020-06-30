#include <centurion_as_ctn.h>

#include "application.h"
#include "random_utils.h"

using namespace wanderer;

int main(int, char**)
{
  math::init_rnd();

  ctn::Centurion c;

  using namespace ctn::hint;
  set_hint<RenderDriver>(RenderDriver::OpenGL);

  ctn::Log::set_priority(ctn::Log::Priority::Info);
  run();
  return 0;
}
#include "parse_portal.hpp"

#include <cassert>  // assert

namespace wanderer::io {

auto parse_portal(const rune::tmx_object& object) -> comp::portal
{
  assert(rune::tmx::is_int(object.properties, "target"));
  assert(rune::tmx::is_file(object.properties, "path"));

  comp::portal portal;

  portal.path = rune::tmx::get_file(object.properties, "path").get();
  portal.target = map_id{rune::tmx::get_int(object.properties, "target")};

  return portal;
}

}  // namespace wanderer::io
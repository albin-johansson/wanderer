#include "parse_container.hpp"

#include <cassert>  // assert

namespace wanderer::io {

auto parse_container(const rune::tmx_object& object) -> comp::inventory
{
  assert(rune::tmx::is_int(object.properties, "capacity"));
  assert(rune::tmx::is_bool(object.properties, "hasRandomLoot"));

  comp::inventory inventory;

  inventory.capacity = rune::tmx::get_int(object.properties, "capacity");
  inventory.items.reserve(inventory.capacity);

  if (rune::tmx::get_bool(object.properties, "hasRandomLoot"))
  {
    // TODO
  }

  return inventory;
}

}  // namespace wanderer::io

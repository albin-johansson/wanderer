#include "cursor_system.hpp"

#include "components/ctx/cursors.hpp"

namespace wanderer::sys {

void enable_cursor(entt::registry& registry, const cen::system_cursor cursor)
{
  auto& cursors = registry.ctx<ctx::cursors>();
  cursors.data.at(cen::system_cursor::hand).enable();
}

}  // namespace wanderer::sys

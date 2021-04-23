#include "cursor_system.hpp"

#include "components/ui/cursors.hpp"

namespace wanderer::sys {

void enable_cursor(entt::registry& registry, const cen::system_cursor cursor)
{
  auto& cursors = registry.ctx<comp::cursors>();  // FIXME comp::cursors -> ctx::cursors
  cursors.data.at(cen::system_cursor::hand).enable();
}

}  // namespace wanderer::sys

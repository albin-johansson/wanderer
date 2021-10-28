#include "cursor_system.hpp"

#include "components/cursors.hpp"

namespace wanderer::sys {

void EnableCursor(entt::registry& registry, const cen::system_cursor cursor)
{
  auto& cursors = registry.ctx<ctx::Cursors>();
  cursors.data.at(cursor).enable();
}

}  // namespace wanderer::sys

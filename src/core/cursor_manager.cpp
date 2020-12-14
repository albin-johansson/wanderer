#include "cursor_manager.hpp"

namespace wanderer {

auto cursor_manager::at(const cen::system_cursor cursor) -> cen::cursor&
{
  if (const auto it = m_cursors.find(cursor); it != m_cursors.end()) {
    return it->second;
  } else {
    auto [iter, wasInserted] = m_cursors.emplace(cursor, cursor);
    return iter->second;
  }
}

}  // namespace wanderer

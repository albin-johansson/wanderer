#pragma once

#include <unordered_map> // unordered_map
#include <cen/cursor.hpp>

namespace wanderer {

class cursor_manager final
{
 public:
  [[nodiscard]] auto at(cen::system_cursor cursor) -> cen::cursor&;

 private:
  std::unordered_map<cen::system_cursor, cen::cursor> m_cursors;
};

}

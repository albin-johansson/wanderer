#pragma once

#include <cen/cursor.hpp>  // cursor, system_cursor
#include <unordered_map>   // unordered_map

namespace wanderer::comp {

struct cursors final
{
  // Unfortunately, we have to explicitly tell the compiler that this type
  // isn't copyable, due to the fact the type trait for checking the
  // "copyable-ness" of the unordered map is misleading
  cursors(const cursors&) = delete;
  cursors(cursors&&) = default;
  cursors& operator=(const cursors&) = delete;
  cursors& operator=(cursors&&) = default;

  std::unordered_map<cen::system_cursor, cen::cursor> data;
};

}  // namespace wanderer::comp

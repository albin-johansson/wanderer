#pragma once

#include <centurion.hpp>  // scan_code

#include "core/menu_action.hpp"

namespace wanderer::comp {

struct key_bind final
{
  cen::scan_code key;
  menu_action action{menu_action::none};
};

}  // namespace wanderer::comp

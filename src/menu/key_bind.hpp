#pragma once

#include <cen/scan_code.hpp>

#include "key_trigger.hpp"
#include "menu_action.hpp"

namespace wanderer {

struct key_bind final
{
  cen::scan_code key;
  menu_action action;
  key_trigger trigger;
};

}  // namespace wanderer

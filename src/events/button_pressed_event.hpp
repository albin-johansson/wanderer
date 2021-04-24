#pragma once

#include "core/menu_action.hpp"

namespace wanderer {

struct button_pressed_event final
{
  menu_action action;
};

}  // namespace wanderer
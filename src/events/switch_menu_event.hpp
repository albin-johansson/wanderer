#pragma once

#include "core/menu_id.hpp"

namespace wanderer::event {

struct switch_menu final
{
  menu_id id;
};

}  // namespace wanderer::event

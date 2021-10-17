#pragma once

#include <centurion.hpp>  // scan_code

#include "core/menu_action.hpp"

namespace wanderer::comp {

struct KeyBind final
{
  cen::scan_code key;
  MenuAction action{MenuAction::None};
};

}  // namespace wanderer::comp

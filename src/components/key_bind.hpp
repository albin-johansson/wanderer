#pragma once

#include <centurion.hpp>  // scan_code

#include "core/action.hpp"

namespace wanderer {

struct KeyBind final
{
  cen::scan_code key;
  Action action{Action::None};
};

}  // namespace wanderer

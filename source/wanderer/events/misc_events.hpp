#pragma once

#include "wanderer/common.hpp"
#include "wanderer/core/action.hpp"

namespace wanderer {

struct action_event final
{
  Action action{Action::noop};
};

}  // namespace wanderer
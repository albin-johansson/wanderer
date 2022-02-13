#pragma once

#include "wanderer/core/action.hpp"

namespace wanderer {

struct action_event final
{
  action_id action{action_id::noop};
};

}  // namespace wanderer
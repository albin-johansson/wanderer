#pragma once

#include "action.hpp"

namespace wanderer {

class quit_action final : public action
{
 public:
  void execute(entt::dispatcher& dispatcher) override;
};

}  // namespace wanderer

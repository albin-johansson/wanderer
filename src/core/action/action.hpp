#pragma once

#include <entt.hpp>  // dispatcher

namespace wanderer {

class action
{
 public:
  virtual ~action() noexcept = default;

  virtual void execute(entt::dispatcher& dispatcher) = 0;
};

}  // namespace wanderer

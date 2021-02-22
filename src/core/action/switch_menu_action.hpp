#pragma once

#include "action.hpp"
#include "menu_id.hpp"

namespace wanderer {

class switch_menu_action final : public action
{
 public:
  explicit switch_menu_action(menu_id id);

  void execute(entt::dispatcher& dispatcher) override;

 private:
  menu_id m_id;
};

}  // namespace wanderer

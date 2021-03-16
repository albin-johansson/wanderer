#include "switch_menu_action.hpp"

#include "switch_menu_event.hpp"

namespace wanderer {

switch_menu_action::switch_menu_action(const menu_id id) : m_id{id}
{}

void switch_menu_action::execute(entt::dispatcher& dispatcher)
{
  dispatcher.enqueue<comp::switch_menu_event>(m_id);
}

}  // namespace wanderer

#pragma once

#include <entt.hpp>  // id_type

#include "io/menu/menu_action.hpp"

namespace wanderer::event {

struct button_pressed final
{
  menu_action action;
  entt::id_type source;
};

}  // namespace wanderer::event
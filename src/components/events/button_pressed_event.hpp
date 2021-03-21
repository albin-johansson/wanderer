#pragma once

#include <entt.hpp>  // id_type

namespace wanderer::comp {

struct button_pressed_event final
{
  entt::id_type source;
};

}  // namespace wanderer::comp
#pragma once

#include "menu.hpp"

namespace wanderer::comp {

// TODO replace with associated_entity?
struct associated_menu final
{
  menu::entity entity{null<menu>()};
};

}  // namespace wanderer::comp

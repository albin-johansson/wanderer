#pragma once

#include <memory>  // unique_ptr

#include "action.hpp"
#include "menu_action.hpp"

namespace wanderer::sys {

[[nodiscard]] auto create_action(const menu_action menuAction)
    -> std::unique_ptr<action>;

}

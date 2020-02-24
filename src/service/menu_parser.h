#pragma once
#include <memory>

#include "menu.h"

namespace albinjohansson {
namespace wanderer {

std::unique_ptr<IMenu> parse_menu(const char* file);

}
}  // namespace albinjohansson
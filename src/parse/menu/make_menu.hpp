#pragma once

#include <filesystem>  // path

#include "menu/menu.hpp"

namespace wanderer {

[[nodiscard]] auto make_menu(const std::filesystem::path& path) -> menu;

}  // namespace wanderer

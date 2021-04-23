#pragma once

#include <entt.hpp>    // registry
#include <filesystem>  // path

#include "components/ui/saves_menu.hpp"

namespace wanderer::sys {

auto make_saves_menu_entry(entt::registry& registry, const std::filesystem::path& path)
    -> comp::saves_menu_entry::entity;

}

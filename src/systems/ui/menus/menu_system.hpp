#pragma once

#include <centurion.hpp>  // keyboard, mouse
#include <entt.hpp>       // registry

#include "graphics_context.hpp"
#include "input.hpp"
#include "menu.hpp"
#include "menu_id.hpp"

namespace wanderer::sys {

auto make_menu(entt::registry& registry,
               std::string title,
               menu_id id,
               bool blocking = true) -> comp::menu::entity;

/**
 * \brief Creates and returns a menu registry.
 *
 * \return a registry with all of the game menus.
 */
[[nodiscard]] auto create_menus() -> entt::registry;

/**
 * \brief Updates the currently active menu.
 *
 * \param registry the menu registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param input the current input state.
 */
void update_menu(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const input& input);

void sync_settings_menu(entt::registry& registry);

/**
 * \brief Changes the currently active menu.
 *
 * \param registry the menu registry.
 * \param id the ID associated with the menu that will be selected.
 */
void switch_menu(entt::registry& registry, menu_id id);

/**
 * \brief Renders the currently active menu.
 *
 * \param registry the menu registry.
 * \param graphics the graphics context that will be used.
 */
void render_menu(const entt::registry& registry, graphics_context& graphics);

/**
 * \brief Indicates whether or not the current menu is blocking.
 *
 * \details A blocking menu is meant to prevent the game from updating.
 *
 * \return `true` if the current menu is blocking; `false` otherwise
 */
[[nodiscard]] auto is_current_menu_blocking(const entt::registry& registry) -> bool;

}  // namespace wanderer::sys

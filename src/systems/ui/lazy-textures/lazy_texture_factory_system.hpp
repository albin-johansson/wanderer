#pragma once

#include <centurion.hpp>  // surface, farea
#include <entt.hpp>       // registry

#include "components/ui/lazy_texture.hpp"
#include "components/ui/menu.hpp"
#include "core/grid_position.hpp"

namespace wanderer::sys {

/// \name UI
/// \{

/**
 * \brief Creates and returns a lazy texture entity.
 *
 * \details The created entity will feature `comp::lazy_texture` and
 * `comp::associated_menu` components.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param menu the associated menu entity.
 * \param surface the source image data.
 * \param position the position of the texture.
 * \param size the rendered size of the texture.
 *
 * \return the created lazy texture entity.
 */
auto make_lazy_texture(entt::registry& registry,
                       comp::menu::entity menu,
                       cen::surface surface,
                       grid_position position,
                       cen::farea size) -> comp::lazy_texture::entity;

/// \} End of UI

}  // namespace wanderer::sys

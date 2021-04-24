#pragma once

#include <entt.hpp>  // registry
#include <string>    // string

#include "components/ui/label.hpp"
#include "components/ui/menu.hpp"
#include "core/grid_position.hpp"
#include "core/text_size.hpp"

namespace wanderer::sys {

/// \name Labels
/// \{

/**
 * \brief Creates a label entity.
 *
 * \details The created entity will feature `comp::label` and `comp::associated_menu`
 * components.
 *
 * \ingroup systems
 *
 * \param registry the menu registry.
 * \param menu the associated menu entity.
 * \param text the text of the label.
 * \param position the position of the label.
 * \param size the size of the label text.
 *
 * \return the created entity.
 */
auto make_label(entt::registry& registry,
                comp::menu::entity menu,
                std::string text,
                grid_position position,
                text_size size = text_size::small) -> comp::label::entity;

/// \} End of labels

}  // namespace wanderer::sys
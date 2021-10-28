#pragma once

#include <string>  // string

#include <entt.hpp>  // registry

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
 * \details The created entity will feature `label` and `associated_menu` components.
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
auto MakeLabel(entt::registry& registry,
               entt::entity menu,
               std::string text,
               GridPosition position,
               TextSize size = TextSize::Small) -> entt::entity;

/// \} End of labels

}  // namespace wanderer::sys

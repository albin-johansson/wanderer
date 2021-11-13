#pragma once

#include <string>  // string

#include <centurion.hpp>  // renderer
#include <entt/entt.hpp>  // registry

#include "components/ui/label.hpp"
#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// \name Labels
/// \{

/**
 * \brief Sets the text associated with a label.
 *
 * \details This function is useful since it will also reset the label texture.
 *
 * \ingroup systems
 *
 * \param label the label that will be modified.
 * \param text the new label text.
 */
void SetText(Label& label, std::string text);

/// \} End of labels

}  // namespace wanderer::sys
#pragma once

#include <centurion.hpp>  // renderer
#include <entt.hpp>       // registry
#include <string>         // string

#include "components/ui/label.hpp"
#include "components/ui/menu.hpp"

namespace wanderer::sys {

/// \name Labels
/// \{

/// Creates a label entity
auto make_label(entt::registry& registry,
                comp::menu::entity menu,
                std::string text,
                float row,
                float col,
                text_size size = text_size::small) -> comp::label::entity;

/// Updates the text of a label
void set_text(comp::label& label, std::string text);

// Renders all labels in the currently active menu
void render_labels(const entt::registry& registry, cen::renderer& renderer);

/// \} End of labels

}  // namespace wanderer::sys
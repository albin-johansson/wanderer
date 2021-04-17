#pragma once

#include <centurion.hpp>  // renderer, texture, font
#include <string>         // string

namespace wanderer {

[[nodiscard]] auto render_text(cen::renderer& renderer,
                               const std::string& text,
                               const cen::font& font) -> cen::texture;

}  // namespace wanderer

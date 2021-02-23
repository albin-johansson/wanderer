#pragma once

#include <cen/font.hpp>      // font
#include <cen/renderer.hpp>  // renderer
#include <cen/texture.hpp>   // texture
#include <string>            // string

namespace wanderer {

[[nodiscard]] auto render_text(cen::renderer& renderer,
                               const std::string& text,
                               const cen::font& font) -> cen::texture;

}  // namespace wanderer

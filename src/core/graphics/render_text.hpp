#pragma once

#include <centurion.hpp>  // renderer, texture, font
#include <string>         // string

namespace wanderer {

[[nodiscard]] auto RenderText(cen::renderer& renderer,
                              const std::string& text,
                              const cen::font& font) -> cen::texture;

}  // namespace wanderer

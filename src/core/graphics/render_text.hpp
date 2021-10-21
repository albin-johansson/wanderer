#pragma once

#include <string>  // string

#include <centurion.hpp>  // renderer, texture, font

namespace wanderer {

[[nodiscard]] auto RenderText(cen::renderer& renderer,
                              const std::string& text,
                              const cen::font& font) -> cen::texture;

}  // namespace wanderer

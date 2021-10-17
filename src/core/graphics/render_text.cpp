#include "render_text.hpp"

namespace wanderer {

auto RenderText(cen::renderer& renderer, const std::string& text, const cen::font& font)
    -> cen::texture
{
  return renderer.render_blended_utf8(text, font);
}

}  // namespace wanderer

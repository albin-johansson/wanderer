#include "render_text.hpp"

#include <cassert>  // assert

namespace wanderer {

auto RenderText(cen::renderer& renderer, const std::string& text, const cen::font& font)
    -> cen::texture
{
  assert(!text.empty());
  return renderer.render_blended_utf8(text, font);
}

}  // namespace wanderer

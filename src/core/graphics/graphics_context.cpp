#include "graphics_context.hpp"

#include <utility>  // move

#include "core/resources.hpp"

namespace wanderer {
namespace {
inline const auto font_path = resources::font("type_writer.ttf");
}  // namespace

GraphicsContext::GraphicsContext(const cen::window& window)
    : mRenderer{window, cen::renderer::accelerated | cen::renderer::target_textures}
    , mFormat{window.get_pixel_format()}
    , mLightCanvas{GetRenderer(),
                   mFormat,
                   cen::texture_access::target,
                   glob::logical_size<>}
{
  mTextures.reserve(10);

  auto& renderer = GetRenderer();
  renderer.set_blend_mode(cen::blend_mode::blend);

  renderer.emplace_font(glob::menu_font_s, font_path, glob::small_font_size);
  renderer.emplace_font(glob::menu_font_m, font_path, glob::medium_font_size);
  renderer.emplace_font(glob::menu_font_l, font_path, glob::large_font_size);

  renderer.set_logical_size(glob::logical_size<>);
  renderer.set_logical_integer_scaling(true);

  EmplaceCache(small_black_font, font_path, glob::small_font_size);
  EmplaceCache(small_font, font_path, glob::small_font_size);
  EmplaceCache(medium_font, font_path, glob::medium_font_size);
  EmplaceCache(large_font, font_path, glob::large_font_size);

  renderer.set_color(cen::colors::black);
  GetCache(small_black_font).add_latin1(renderer);

  renderer.set_color(cen::colors::white);
  GetCache(small_font).add_latin1(renderer);
  GetCache(medium_font).add_latin1(renderer);
  GetCache(large_font).add_latin1(renderer);

  mLightCanvas.set_blend_mode(cen::blend_mode::mul);
}

auto GraphicsContext::LoadTexture(uint32 id, const std::string& path) -> usize
{
  if (const auto it = mIndices.find(id); it != mIndices.end()) {
    return it->second;
  }
  else {
    const auto index = mTextures.size();

    mTextures.emplace_back(mRenderer, path);
    mIndices.try_emplace(id, index);

    return index;
  }
}

}  // namespace wanderer

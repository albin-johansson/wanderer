#include "text.hpp"

#include <utility>  // move

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer {

ui_text::ui_text(std::string text, const font_size size)
    : mText{std::move(text)}
    , mFontSize{size}
{}

void ui_text::init(graphics_ctx& graphics)
{
  auto& renderer = graphics.renderer();

  if (!mTexture.has_value()) {
    auto& font = graphics.get_pixelated_font(mFontSize);

    auto surface = font.render_blended(mText.c_str(), cen::colors::white);
    mTexture = renderer.create_texture(surface);
    mTextureSize = mTexture->size();
  }
}

void ui_text::render(graphics_ctx& graphics, const glm::vec2& pos)
{
  if (!mTexture.has_value()) {
    init(graphics);
  }

  WANDERER_ASSERT(mTexture.has_value());
  WANDERER_ASSERT(mTextureSize.has_value());

  auto& renderer = graphics.renderer();

  float x{};
  float y{};

  if (pos.x == centered) {
    const auto logicalSize = renderer.logical_size();
    x = static_cast<float>(logicalSize.width - mTextureSize->width) / 2.0f;
  }
  else {
    x = pos.x;
  }

  if (pos.y == centered) {
    const auto logicalSize = renderer.logical_size();
    y = static_cast<float>(logicalSize.height - mTextureSize->height) / 2.0f;
  }
  else {
    y = pos.y;
  }

  renderer.render(mTexture.value(), cen::fpoint{x, y});
}

auto ui_text::is_initialized() const -> bool
{
  return mTexture.has_value() && mTextureSize.has_value();
}

auto ui_text::get_size() const -> const maybe<cen::iarea>&
{
  return mTextureSize;
}

}  // namespace wanderer
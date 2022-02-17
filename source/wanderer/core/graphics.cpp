#include "graphics.hpp"

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/misc/assert.hpp"
#include "wanderer/misc/exception.hpp"
#include "wanderer/misc/logging.hpp"

#undef small

namespace wanderer {
namespace {

constexpr auto _window_flags = cen::window::hidden | cen::window::allow_high_dpi;

constexpr auto _renderer_flags = cen::renderer::accelerated |      //
                                 cen::renderer::target_textures |  //
                                 cen::renderer::vsync;

constexpr int _pixelated_size_s = 8;
constexpr int _pixelated_size_m = _pixelated_size_s * 2;
constexpr int _pixelated_size_l = _pixelated_size_s * 3;

constexpr int _handwriting_size_s = 9;
constexpr int _handwriting_size_m = 12;
constexpr int _handwriting_size_l = 16;

}  // namespace

graphics_ctx::graphics_ctx(const game_cfg& cfg)
    : mWindow{"Wanderer", cen::window::default_size(), _window_flags}
    , mRenderer{mWindow.create_renderer(_renderer_flags)}
{
  const cen::iarea size{cfg.logical_size.x, cfg.logical_size.y};
  mWindow.set_size(size);

  mRenderer.set_logical_size(size);
  mRenderer.set_blend_mode(cen::blend_mode::blend);

  const char* pixelatedPath = "resources/fonts/type_writer.ttf";
  mPixelatedFontId = mFontBundle.load_font(pixelatedPath, _pixelated_size_s);
  mFontBundle.load_font(pixelatedPath, _pixelated_size_m);
  mFontBundle.load_font(pixelatedPath, _pixelated_size_l);

  const char* handwritingPath = "resources/fonts/daniel.ttf";
  mHandwritingFontId = mFontBundle.load_font(handwritingPath, _handwriting_size_s);
  mFontBundle.load_font(handwritingPath, _handwriting_size_m);
  mFontBundle.load_font(handwritingPath, _handwriting_size_l);

  debug("Output size... {}", mRenderer.output_size());
}

auto graphics_ctx::load_texture(const std::filesystem::path& path) -> texture_id
{
  /* This approach requires that textures are never removed, which is fine  */
  const auto id = mTextures.size();
  debug("Loading texture '{}' from {}", id, path);

  mTextures.push_back(mRenderer.create_texture(path));
  return id;
}

void graphics_ctx::render_texture(const texture_id id,
                                  const glm::ivec4& source,
                                  const glm::vec4& dest)
{
  WANDERER_ASSERT_MSG(id < mTextures.size(), "Invalid texture identifier!");
  const auto& texture = mTextures[id];
  mRenderer.render(texture, as_rect(source), as_rect(dest));
}

auto graphics_ctx::get_pixelated_font(const font_size size) -> cen::font&
{
  switch (size) {
    case font_size::small:
      return mFontBundle.at(mPixelatedFontId, _pixelated_size_s).get_font();

    case font_size::medium:
      return mFontBundle.at(mPixelatedFontId, _pixelated_size_m).get_font();

    case font_size::large:
      return mFontBundle.at(mPixelatedFontId, _pixelated_size_l).get_font();

    default:
      throw_traced(wanderer_error{"Invalid font size!"});
  }
}

auto graphics_ctx::get_handwriting_font(const font_size size) -> cen::font&
{
  switch (size) {
    case font_size::small:
      return mFontBundle.at(mHandwritingFontId, _handwriting_size_s).get_font();

    case font_size::medium:
      return mFontBundle.at(mHandwritingFontId, _handwriting_size_m).get_font();

    case font_size::large:
      return mFontBundle.at(mHandwritingFontId, _handwriting_size_l).get_font();

    default:
      throw_traced(wanderer_error{"Invalid font size!"});
  }
}

auto graphics_ctx::window() -> cen::window&
{
  return mWindow;
}

auto graphics_ctx::renderer() -> cen::renderer&
{
  return mRenderer;
}

}  // namespace wanderer
#include "graphics.hpp"

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/io/settings.hpp"
#include "wanderer/meta/build.hpp"
#include "wanderer/misc/assert.hpp"
#include "wanderer/misc/exception.hpp"
#include "wanderer/misc/logging.hpp"
#include "win32.hpp"

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
constexpr int _pixelated_size_h = _pixelated_size_s * 5;

constexpr int _handwriting_size_s = 9;
constexpr int _handwriting_size_m = 12;
constexpr int _handwriting_size_l = 16;
constexpr int _handwriting_size_h = 32;

}  // namespace

graphics_ctx::graphics_ctx(const game_cfg& cfg, const settings& s)
    : mWindow{"Wanderer", cen::window::default_size(), _window_flags}
    , mRenderer{mWindow.create_renderer(_renderer_flags)}
{
  const cen::iarea size{cfg.logical_size.x, cfg.logical_size.y};
  mWindow.set_size(size);

  win32::use_immersive_dark_mode(mWindow);

  mRenderer.set_logical_size(size);
  // mRenderer.set_logical_integer_scaling(true);
  mRenderer.set_blend_mode(cen::blend_mode::blend);

  const char* pixelatedPath = "resources/fonts/type_writer.ttf";
  mPixelatedFontId = mFontBundle.load_font(pixelatedPath, _pixelated_size_s);
  mFontBundle.load_font(pixelatedPath, _pixelated_size_m);
  mFontBundle.load_font(pixelatedPath, _pixelated_size_l);
  mFontBundle.load_font(pixelatedPath, _pixelated_size_h);

  const char* handwritingPath = "resources/fonts/daniel.ttf";
  mHandwritingFontId = mFontBundle.load_font(handwritingPath, _handwriting_size_s);
  mFontBundle.load_font(handwritingPath, _handwriting_size_m);
  mFontBundle.load_font(handwritingPath, _handwriting_size_l);
  mFontBundle.load_font(handwritingPath, _handwriting_size_h);

  mWindow.set_fullscreen_desktop(s.test_flag(settings::fullscreen_bit));

  mVsync = s.test_flag(settings::vsync_bit);
  mRenderer.set_vsync(mVsync);
}

auto graphics_ctx::toggle_fullscreen() -> bool
{
  const auto enabled = !mWindow.is_fullscreen_desktop();
  debug("Fullscreen mode is now {}", enabled ? "enabled" : "disabled");

  mWindow.set_fullscreen_desktop(enabled);
  return mWindow.is_fullscreen_desktop();
}

auto graphics_ctx::toggle_vsync() -> bool
{
  mVsync = !mVsync;
  debug("VSync is now {}", mVsync ? "enabled" : "disabled");

  mRenderer.set_vsync(mVsync);
  return mVsync;
}

auto graphics_ctx::load_texture(const std::filesystem::path& path) -> texture_id
{
  /* This approach requires that textures are never removed, which is fine  */
  const auto id = mTextures.size();
  debug("Loading texture '{}' from {}", id, path);

#if WANDERER_COMPILER_MSVC
  mTextures.push_back(mRenderer.create_texture(path.string()));
#else
  mTextures.push_back(mRenderer.create_texture(path));
#endif  // WANDERER_COMPILER_MSVC

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

    case font_size::huge:
      return mFontBundle.at(mPixelatedFontId, _pixelated_size_h).get_font();

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

    case font_size::huge:
      return mFontBundle.at(mHandwritingFontId, _handwriting_size_h).get_font();

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
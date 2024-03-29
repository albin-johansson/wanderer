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

Graphics::Graphics(const GameConfig& cfg, const Settings& s)
    : mWindow{"Wanderer", cen::window::default_size(), _window_flags}
    , mRenderer{mWindow.create_renderer(_renderer_flags)}
    , mLightCanvas{mRenderer.create_texture(as_area(cfg.logical_size),
                                            mWindow.format(),
                                            cen::texture_access::target)}
{
  mWindow.set_size(as_area(cfg.logical_size));

  win32::use_immersive_dark_mode(mWindow);

  mRenderer.set_logical_size(as_area(cfg.logical_size));
  mRenderer.set_logical_integer_scaling(s.test_flag(Settings::integer_scaling_bit));
  mRenderer.set_blend_mode(cen::blend_mode::blend);
  mLightCanvas.set_blend_mode(cen::blend_mode::mul);

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

  mWindow.set_fullscreen_desktop(s.test_flag(Settings::fullscreen_bit));

  mVsync = s.test_flag(Settings::vsync_bit);
  mRenderer.set_vsync(mVsync);

  mLightTextureId = load_texture("resources/images/ardentryst/glow.png");
}

auto Graphics::toggle_fullscreen() -> bool
{
  const auto enabled = !mWindow.is_fullscreen_desktop();
  debug("Fullscreen mode is now {}", enabled ? "enabled" : "disabled");

  mWindow.set_fullscreen_desktop(enabled);
  return mWindow.is_fullscreen_desktop();
}

auto Graphics::toggle_vsync() -> bool
{
  mVsync = !mVsync;
  debug("VSync is now {}", mVsync ? "enabled" : "disabled");

  mRenderer.set_vsync(mVsync);
  return mVsync;
}

auto Graphics::toggle_integer_scaling() -> bool
{
  const auto enabled = !mRenderer.using_integer_logical_scaling();
  debug("Integer scaling is now {}", enabled ? "enabled" : "disabled");

  mRenderer.set_logical_integer_scaling(enabled);
  return mRenderer.using_integer_logical_scaling();
}

auto Graphics::load_texture(const std::filesystem::path& path) -> texture_id
{
  /* This approach requires that textures are never removed, which is fine  */
  const auto id = mTextures.size();
  debug("Loading texture '{}' from {}", id, path.string());

#if WANDERER_COMPILER_MSVC
  mTextures.push_back(mRenderer.create_texture(path.string()));
#else
  mTextures.push_back(mRenderer.create_texture(path));
#endif  // WANDERER_COMPILER_MSVC

  return id;
}

void Graphics::render_texture(const texture_id id,
                                  const glm::ivec4& source,
                                  const glm::vec4& dest)
{
  render_texture(id, as_rect(source), as_rect(dest));
}

void Graphics::render_texture(const texture_id id,
                                  const cen::irect& source,
                                  const cen::frect& dest)
{
  WANDERER_ASSERT_MSG(id < mTextures.size(), "Invalid texture identifier!");
  const auto& texture = mTextures[id];
  mRenderer.render(texture, source, dest);
}

void Graphics::render_light(const cen::frect& dest)
{
  constexpr cen::irect source{0, 0, 80, 80};
  render_texture(mLightTextureId, source, dest);
}

auto Graphics::get_light_canvas() -> cen::texture&
{
  return mLightCanvas;
}

auto Graphics::get_pixelated_font(const FontSize size) -> cen::font&
{
  switch (size) {
    case FontSize::small:
      return mFontBundle.at(mPixelatedFontId, _pixelated_size_s).get_font();

    case FontSize::medium:
      return mFontBundle.at(mPixelatedFontId, _pixelated_size_m).get_font();

    case FontSize::large:
      return mFontBundle.at(mPixelatedFontId, _pixelated_size_l).get_font();

    case FontSize::huge:
      return mFontBundle.at(mPixelatedFontId, _pixelated_size_h).get_font();

    default:
      throw_traced(WandererError{"Invalid font size!"});
  }
}

auto Graphics::get_handwriting_font(const FontSize size) -> cen::font&
{
  switch (size) {
    case FontSize::small:
      return mFontBundle.at(mHandwritingFontId, _handwriting_size_s).get_font();

    case FontSize::medium:
      return mFontBundle.at(mHandwritingFontId, _handwriting_size_m).get_font();

    case FontSize::large:
      return mFontBundle.at(mHandwritingFontId, _handwriting_size_l).get_font();

    case FontSize::huge:
      return mFontBundle.at(mHandwritingFontId, _handwriting_size_h).get_font();

    default:
      throw_traced(WandererError{"Invalid font size!"});
  }
}

auto Graphics::window() -> cen::window&
{
  return mWindow;
}

auto Graphics::renderer() -> cen::renderer&
{
  return mRenderer;
}

}  // namespace wanderer
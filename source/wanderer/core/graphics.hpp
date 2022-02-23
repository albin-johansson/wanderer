#pragma once

#include <centurion.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

/* On MSVC using the Visual Studio 2022 toolchain, a Windows header leaks this macro :( */
#undef small

namespace wanderer {

/**
 * \brief Represents the different supported font sizes.
 */
enum class font_size
{
  small,
  medium,
  large,
  huge
};

/**
 * \brief Manages the game window and renderer, along with fonts and textures.
 */
class graphics_ctx final
{
 public:
  graphics_ctx(const game_cfg& cfg, const settings& s);

  /**
   * \brief Toggles the fullscreen mode of the window.
   *
   * \return `true` if the window is now fullscreen; `false` otherwise.
   */
  auto toggle_fullscreen() -> bool;

  /**
   * \brief Toggles the use of VSync by the renderer.
   *
   * \return `true` if VSync was enabled; `false` otherwise.
   */
  auto toggle_vsync() -> bool;

  /**
   * \brief Toggles the use of integer scaling by the renderer.
   *
   * \return `true` if integer scaling was enabled; `false` otherwise.
   */
  auto toggle_integer_scaling() -> bool;

  /**
   * \brief Loads a texture.
   *
   * \param path the file path to the source texture.
   *
   * \return the assigned texture identifier.
   */
  auto load_texture(const std::filesystem::path& path) -> texture_id;

  /**
   * \brief Renders a previously loaded texture.
   *
   * \param id the identifier associated with the texture to render.
   * \param source the source region of the texture to render.
   * \param dest the destination position and size of the texture.
   */
  void render_texture(texture_id id, const glm::ivec4& source, const glm::vec4& dest);

  [[nodiscard]] auto get_pixelated_font(font_size size) -> cen::font&;

  [[nodiscard]] auto get_handwriting_font(font_size size) -> cen::font&;

  [[nodiscard]] auto window() -> cen::window&;

  [[nodiscard]] auto renderer() -> cen::renderer&;

 private:
  cen::window mWindow;
  cen::renderer mRenderer;

  /* Texture identifiers are just indices into this vector */
  std::vector<cen::texture> mTextures;

  cen::font_bundle mFontBundle;
  cen::font_bundle::id_type mPixelatedFontId;
  cen::font_bundle::id_type mHandwritingFontId;

  bool mVsync{};
};

}  // namespace wanderer
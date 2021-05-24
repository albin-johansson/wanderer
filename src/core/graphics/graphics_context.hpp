#pragma once

#include <centurion.hpp>  // window, texture
#include <rune.hpp>       // graphics

#include "core/aliases/ints.hpp"
#include "core/aliases/texture_id.hpp"
#include "core/aliases/texture_index.hpp"
#include "core/menu_constants.hpp"

namespace wanderer {

class graphics_context final : public rune::graphics
{
  inline static constexpr font_id small_font = 0;
  inline static constexpr font_id medium_font = 1;
  inline static constexpr font_id large_font = 2;
  inline static constexpr font_id small_black_font = 3;

 public:
  /**
   * \brief Initializes the graphics context.
   *
   * \param window the game window.
   * \param flags the renderer flags.
   */
  explicit graphics_context(const cen::window& window, uint32 flags);

  /**
   * \brief Renders a texture.
   *
   * \pre `index` must be associated with an existing texture.
   *
   * \details This is a convenience function that looks up the texture associated with the
   * supplied index.
   *
   * \pre `index` must be associated with an existing texture.
   *
   * \param index the index of the texture that will be rendered.
   * \param src the region of the texture that will be rendered.
   * \param dst the destination rectangle.
   */
  void render(const texture_index index,
              const cen::irect& src,
              const cen::frect& dst) noexcept
  {
    renderer().render_t(at(index), src, dst);
  }

  /**
   * \brief Renders small white text with a black outline.
   *
   * \note The text parameter is generic due to funky overloads of `render_text`.
   *
   * \param text the string that will be rendered.
   * \param position the position of the rendered string.
   */
  void render_outlined_text(const auto& text, const cen::ipoint& position)
  {
    const auto& black = small_black_font_cache();
    const auto& white = small_font_cache();

    auto& ren = renderer();
    ren.render_text(black, text, position + cen::point(1, 1));
    ren.render_text(white, text, position);
  }

  /**
   * \brief Returns the font cache for the "small" black font.
   *
   * \see `glob::small_font_size`
   *
   * \return the font cache for the smallest black font.
   */
  [[nodiscard]] auto small_black_font_cache() noexcept -> cen::font_cache&
  {
    return get_cache(small_black_font);
  }

  /**
   * \brief Returns the font cache for the "small" font.
   *
   * \see `glob::small_font_size`
   *
   * \return the font cache for the smallest font.
   */
  [[nodiscard]] auto small_font_cache() noexcept -> cen::font_cache&
  {
    return get_cache(small_font);
  }

  /**
   * \brief Returns the font cache for the "medium" font.
   *
   * \see `glob::medium_font_size`
   *
   * \return the font cache for the medium font.
   */
  [[nodiscard]] auto medium_font_cache() noexcept -> cen::font_cache&
  {
    return get_cache(medium_font);
  }

  /**
   * \brief Returns the font cache for the "large" font.
   *
   * \see `glob::large_font_size`
   *
   * \return the font cache for the largest font.
   */
  [[nodiscard]] auto large_font_cache() noexcept -> cen::font_cache&
  {
    return get_cache(large_font);
  }

  /**
   * \brief Returns the texture intended to be used as a canvas "overlay" for rendering
   * lights.
   *
   * \return the light rendering canvas.
   */
  [[nodiscard]] auto light_canvas() noexcept -> cen::texture&
  {
    return m_lightCanvas;
  }

 private:
  cen::texture m_lightCanvas;  // Used as a rendering target for simulating lights
};

}  // namespace wanderer

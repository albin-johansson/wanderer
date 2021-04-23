#pragma once

#include <cassert>        // assert
#include <centurion.hpp>  // renderer, texture
#include <cstddef>        // size_t
#include <string>         // string
#include <unordered_map>  // unordered_map
#include <vector>         // vector

#include "core/aliases/texture_id.hpp"
#include "core/aliases/texture_index.hpp"

namespace wanderer {

/**
 * \brief The main graphics API, meant to be passed to rendering systems.
 *
 * \details This class provides a renderer, efficient texture handling, font caches for
 * efficient text rendering, a light rendering texture canvas, etc.
 *
 * \details For reduced memory consumption and simpler components, graphics components
 * only contain texture indices, which can be obtained from this class. These indices
 * literally correspond to indices to an array of textures managed by this class, which
 * results in very fast constant-complexity lookup of textures. Furthermore, this class
 * will actively avoid loading the same texture more than once.
 *
 * \headerfile graphics_context.hpp
 */
class graphics_context final
{
 public:
  /**
   * \brief Initializes the graphics context.
   *
   * \param window the game window.
   */
  explicit graphics_context(const cen::window& window);

  /**
   * \brief Loads a texture and returns the associated index.
   *
   * \details If a texture with the specified ID has already been loaded, then this
   * function will do nothing, and just returns the existing texture index.
   *
   * \param id the unique ID of the texture.
   * \param path the file path of the texture.
   *
   * \return the index of the loaded texture.
   */
  auto load(texture_id id, std::string path) -> texture_index;

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
    m_renderer.render_t(find(index), src, dst);
  }

  /**
   * \brief Returns the texture associated with the specified index.
   *
   * \details This function uses a very fast index lookup for finding the associated
   * texture. This function is not bounds checked in optimized builds, but an assertion
   * will abort the execution of the program in debug builds if an invalid index is used.
   *
   * \pre `index` must be associated with an existing texture.
   *
   * \param index the index of the desired texture.
   *
   * \return the texture associated with the index.
   */
  [[nodiscard]] auto find(const texture_index index) const noexcept -> const cen::texture&
  {
    assert(index < m_textures.size());  // texture_index is unsigned
    return m_textures[index];
  }

  /**
   * \brief Returns the texture index associated with the specified ID.
   *
   * \pre `id` must be associated with an existing texture.
   *
   * \param id the ID associated with the texture.
   *
   * \return the index of the specified texture.
   */
  [[nodiscard]] auto to_index(const texture_id id) const -> texture_index
  {
    return m_identifiers.at(id);
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
    return m_smallFontCache;
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
    return m_mediumFontCache;
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
    return m_largeFontCache;
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

  /// Returns the associated renderer
  [[nodiscard]] auto renderer() noexcept -> cen::renderer&
  {
    return m_renderer;
  }

  /// Returns the pixel format of the associated window.
  [[nodiscard]] auto pixel_format() const noexcept -> cen::pixel_format
  {
    return m_format;
  }

 private:
  cen::renderer m_renderer;
  std::vector<cen::texture> m_textures;

  cen::font_cache m_smallFontCache;
  cen::font_cache m_mediumFontCache;
  cen::font_cache m_largeFontCache;

  // Used as a rendering target for simulating lights
  cen::texture m_lightCanvas;
  cen::pixel_format m_format;

  // We store used IDs so that we avoid loading the same texture more than once
  std::unordered_map<texture_id, texture_index> m_identifiers;
};

}  // namespace wanderer

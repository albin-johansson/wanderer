#pragma once

#include <unordered_map>  // unordered_map

#include <centurion.hpp>

#include "core/game_constants.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

/**
 * \brief Provides the main graphics API.
 *
 * \details This class provides a renderer, efficient texture handling, font caches for
 * efficient text rendering, pixel format information, etc.
 *
 * \details For reduced memory consumption and redundancy in loaded textures, this class
 * manages a collection of textures that are given unique indices when loaded. These
 * indices literally correspond to indices in an array of textures managed by this class,
 * which results in very fast constant complexity lookup of textures.
 */
class GraphicsContext final
{
  static constexpr uint32 small_font = 0;
  static constexpr uint32 medium_font = 1;
  static constexpr uint32 large_font = 2;
  static constexpr uint32 small_black_font = 3;

 public:
  /**
   * \brief Initializes the graphics context.
   *
   * \param window the game window.
   */
  explicit GraphicsContext(const cen::window& window);

  /**
   * \brief Loads a texture and returns the associated index.
   *
   * \details If a texture with the specified ID has already been loaded, then this
   * function does nothing, and just returns the existing texture index.
   *
   * \param id the unique ID of the texture.
   * \param path the file path of the texture.
   *
   * \return the index of the loaded texture.
   */
  auto load(uint32 id, const std::string& path) -> usize;

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
  void render(const usize index, const cen::irect& src, const cen::frect& dst) noexcept
  {
    mRenderer.render_t(at(index), src, dst);
  }

  /**
   * \brief Renders small white text with a black outline.
   *
   * \note The text parameter is generic due to funky overloads of `RenderText`.
   *
   * \param text the string that will be rendered.
   * \param position the position of the rendered string.
   */
  void render_outlined_text(const auto& text, const cen::ipoint& position)
  {
    const auto& black = small_black_font_cache();
    const auto& white = small_font_cache();

    auto& renderer = get_renderer();
    renderer.render_text(black, text, position + cen::point(1, 1));
    renderer.render_text(white, text, position);
  }

  [[nodiscard]] auto small_black_font_cache() noexcept -> cen::font_cache&
  {
    return get_cache(small_black_font);
  }

  [[nodiscard]] auto small_font_cache() noexcept -> cen::font_cache&
  {
    return get_cache(small_font);
  }

  [[nodiscard]] auto medium_font_cache() noexcept -> cen::font_cache&
  {
    return get_cache(medium_font);
  }

  [[nodiscard]] auto large_font_cache() noexcept -> cen::font_cache&
  {
    return get_cache(large_font);
  }

  /// \brief Returns the texture used as a canvas "overlay" for rendering lights.
  [[nodiscard]] auto light_canvas() noexcept -> cen::texture&
  {
    return mLightCanvas;
  }

  /// \brief Returns the texture associated with the specified index.
  [[nodiscard]] auto at(const usize index) const -> const cen::texture&
  {
    assert(index < mTextures.size());  // texture_index is unsigned
    return mTextures[index];
  }

  /// \copydoc at()
  [[nodiscard]] auto operator[](const usize index) const -> const cen::texture&
  {
    return at(index);
  }

  /**
   * \brief Indicates whether or not a texture index is associated with a texture.
   *
   * \param index the texture index that will be checked.
   *
   * \return `true` if the texture index is associated with a texture; `false` otherwise.
   */
  [[nodiscard]] auto contains(const usize index) const noexcept -> bool
  {
    return index < mTextures.size();
  }

  /**
   * \brief Returns the texture index associated with the specified ID.
   *
   * \param id the ID associated with the texture.
   *
   * \return the index of the specified texture.
   *
   * \throws std::out_of_range if the supplied ID isn't associated with an index.
   */
  [[nodiscard]] auto to_index(const uint32 id) const -> usize
  {
    return mIndices.at(id);
  }

  /**
   * \brief Adds a font cache to the graphics context.
   *
   * \tparam Args the types of the font cache constructor arguments.
   *
   * \note Any previous font cache associated with the supplied ID is overwritten.
   *
   * \param id the unique ID that will be associated with the font cache.
   * \param args the arguments that will be forwarded to an appropriate font cache
   * constructor.
   */
  template <typename... Args>
  void emplace_cache(const uint32 id, Args&&... args)
  {
    mCaches.insert_or_assign(id, cen::font_cache{std::forward<Args>(args)...});
  }

  /**
   * \brief Returns the font cache associated with the specified ID.
   *
   * \param id the ID associated with the desired font cache.
   *
   * \return the found font cache.
   *
   * \throws std::out_of_range if there is no font cache associated with the ID.
   */
  [[nodiscard]] auto get_cache(const uint32 id) -> cen::font_cache&
  {
    return mCaches.at(id);
  }

  /// \copydoc get_cache()
  [[nodiscard]] auto get_cache(const uint32 id) const -> const cen::font_cache&
  {
    return mCaches.at(id);
  }

  [[nodiscard]] auto get_font(const uint32 id) -> cen::font&
  {
    return get_cache(id).get_font();
  }

  [[nodiscard]] auto get_font(const uint32 id) const -> const cen::font&
  {
    return get_cache(id).get_font();
  }

  /// \brief Indicates whether or not there is a font cache associated with an ID.
  [[nodiscard]] auto contains_cache(const uint32 id) const -> bool
  {
    return mCaches.contains(id);
  }

  [[nodiscard]] auto get_renderer() noexcept -> cen::renderer&
  {
    return mRenderer;
  }

  [[nodiscard]] auto get_renderer() const noexcept -> const cen::renderer&
  {
    return mRenderer;
  }

  [[nodiscard]] auto format() const noexcept -> cen::pixel_format
  {
    return mFormat;
  }

 private:
  cen::renderer mRenderer;
  cen::pixel_format mFormat;
  std::vector<cen::texture> mTextures;
  std::unordered_map<uint32, usize> mIndices;
  std::unordered_map<uint32, cen::font_cache> mCaches;
  cen::texture mLightCanvas;  // Used as a rendering target for simulating lights
};

}  // namespace wanderer

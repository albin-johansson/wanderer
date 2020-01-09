#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "rectangle.h"
#include "viewport.h"

namespace centurion {

class Image;
class Font;

/**
 * The Renderer class is a wrapper class for the SDL_Renderer struct. Rendering operations are
 * treated as const methods.
 *
 * @see SDL_Renderer
 * @since 0.1.0
 */
class Renderer final {
 private:
  SDL_Renderer* renderer = nullptr;
  albinjohansson::wanderer::Viewport translationViewport;

 public:
  // TODO a lot of rendering class would be prettier if there was a viewport-translated
  // alternative for all methods, ex: RenderTranslatedRect, RenderTranslatedImage, etc.

  /**
   * Creates a renderer based on the supplied SDL_Renderer.
   *
   * @param renderer a pointer to the SDL_Renderer that will be used by the
   * renderer. Note! The created renderer will take ownership of the supplied
   * pointer, and as such, will free it upon destruction.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit Renderer(SDL_Renderer* renderer);

  /**
   * Creates a renderer based on the supplied SDL_Window. The internal renderer will be created
   * using the SDL_RENDERER_ACCELERATED and SDL_RENDERER_PRESENTVSYNC flags.
   *
   * @param window a pointer to the SDL_Window that will be used to create the
   * renderer.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit Renderer(SDL_Window* window,
                    uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  ~Renderer();

  /**
   * Clears the rendering target with the currently selected color.
   *
   * @since 0.1.0
   */
  void clear() const noexcept;

  /**
   * Applies the previous rendering calls to the rendering target.
   *
   * @since 0.1.0
   */
  void present() const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @since 0.1.0
   */
  void draw_image(const Image& texture, int x, int y) const noexcept;

  void draw_image(const Image& texture, float x, float y) const noexcept;

  /**
   * Renders a texture. This method has no effect if the supplied width and/or height isn't
   * greater than zero.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @param width the width of the rendered texture.
   * @param height the height of the rendered texture.
   * @since 0.1.0
   */
  void draw_image(const Image& texture, int x, int y, int width, int height) const noexcept;

  /**
   * Renders a texture. This method has no effect if the supplied width and/or height isn't greater
   * than zero.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @param width the width of the rendered texture.
   * @param height the height of the rendered texture.
   * @since 0.1.0
   */
  void draw_image(const Image& texture,
                  float x,
                  float y,
                  float width,
                  float height) const noexcept;

  void draw_image(const Image& texture,
                  const albinjohansson::wanderer::Rectangle& source,
                  const albinjohansson::wanderer::FRectangle& destination) const noexcept;

  void draw_image_translated(const Image& texture,
                             const albinjohansson::wanderer::Rectangle& source,
                             const albinjohansson::wanderer::FRectangle& destination) const noexcept;

  /**
   * Renders a filled rectangle with the currently selected color. This method has no effect if the
   * supplied width and/or height isn't greater than zero.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 0.1.0
   */
  void fill_rect(int x, int y, int width, int height) const noexcept;

  /**
   * Renders a filled rectangle with the currently selected color. This method has no effect if the
   * supplied width and/or height isn't greater than zero.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 0.1.0
   */
  void fill_rect(float x, float y, float width, float height) const noexcept;

  /**
   * Renders an outlined rectangle with the currently selected color. This method has no effect if
   * the supplied width and/or height isn't greater than zero.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 0.1.0
   */
  void draw_rect(float x, float y, float width, float height) const noexcept;

  /**
   * Renders an outlined rectangle with the currently selected color. This method has no effect if
   * the supplied width and/or height isn't greater than zero.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 0.1.0
   */
  void draw_rect(int x, int y, int width, int height) const noexcept;

  void draw_text(const std::string& text, float x, float y, const Font& font) const;

  /**
   * Sets the color that will be used by the renderer.
   *
   * @param red the red component value, in the range [0, 255].
   * @param green the green component value, in the range [0, 255].
   * @param blue the blue component value, in the range [0, 255].
   * @param alpha the alpha component value, in the range [0, 255]. Set to 255 by default.
   * @since 0.1.0
   */
  void set_color(uint8_t red,
                 uint8_t green,
                 uint8_t blue,
                 uint8_t alpha = SDL_ALPHA_OPAQUE) const noexcept; // FIXME const

  /**
   * Sets the viewport that will be used by the renderer.
   *
   * @param viewport the viewport that will be used by the renderer.
   * @since 0.1.0
   */
  void set_viewport(const albinjohansson::wanderer::FRectangle& viewport) noexcept;

  void set_translation_viewport(const albinjohansson::wanderer::Viewport& viewport) noexcept;

  void set_blend_mode(const SDL_BlendMode& blendMode) noexcept;

  /**
   * Sets the viewport that will be used by the renderer. This method has no effect if any of the
   * arguments are less than or equal to zero.
   *
   * @param xScale the x-axis scale that will be used.
   * @param yScale the y-axis scale that will be used.
   * @since 0.1.0
   */
  void set_scale(float xScale, float yScale) noexcept;

  /**
   * Sets the logical dimensions of the renderer, which is useful for achieving
   * resolution-independent rendering. This method has no effect if either of the supplied
   * dimensions aren't greater than zero.
   *
   * @param width the logical width that will be used.
   * @param height the logical height that will be used.
   * @since 0.1.0
   */
  void set_logical_size(float width, float height) noexcept;

  /**
   * Sets whether or not to force integer scaling for the logical viewport. By default, this
   * property is set to false.
   *
   * @param useLogicalIntegerScale true if integer scaling should be used; false otherwise.
   * @since 0.1.0
   */
  void set_logical_integer_scale(bool useLogicalIntegerScale) noexcept;

  /**
   * Returns the logical width that the renderer uses.
   *
   * @return the logical width that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_logical_width() const noexcept;

  /**
   * Returns the logical height that the renderer uses.
   *
   * @return the logical height that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_logical_height() const noexcept;

  /**
   * Returns the x-axis scale that the renderer uses.
   *
   * @return the x-axis scale that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]]
  float get_x_scale() const noexcept;

  /**
   * Returns the y-axis scale that the renderer uses.
   *
   * @return the y-axis scale that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]]
  float get_y_scale() const noexcept;

  /**
   * Indicates whether or not the renderer uses integer scaling values for logical viewports. By
   * default, this property is set to false.
   *
   * @return true if the renderer uses integer scaling for logical viewports; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool is_using_integer_logical_scaling() const noexcept;

  /**
   * Attempts to create and return a pointer to an SDL_Texture instance that represents the
   * supplied string rendered with the supplied font. This method will not throw any
   * exception by itself, but dynamic memory allocation will occur behind-the-scenes.
   *
   * @param s the string that contains the content that will be rendered to a texture.
   * @param font a reference to the font that will be used.
   * @return a unique pointer to an image that represents the supplied string rendered with the
   * currently selected font; nullptr if the operation is unsuccessful.
   */
  [[nodiscard]]
  std::unique_ptr<Image> create_image(const std::string& s, const Font& font) const;

  /**
   * Returns the viewport that the renderer uses.
   *
   * @return the viewport that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]]
  albinjohansson::wanderer::FRectangle get_viewport() const noexcept;

  [[nodiscard]]
  const albinjohansson::wanderer::Viewport& get_translation_viewport() const noexcept;

  operator SDL_Renderer*() const noexcept;
};

}
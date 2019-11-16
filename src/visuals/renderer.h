#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "rectangle.h"
#include "font.h"

namespace wanderer::visuals {

class Renderer;

using Renderer_uptr = std::unique_ptr<Renderer>;
using Renderer_sptr = std::shared_ptr<Renderer>;
using Renderer_wptr = std::weak_ptr<Renderer>;

/**
 * The Renderer class is a wrapper class for the SDL_Renderer struct.
 *
 * @see SDL_Renderer
 * @since 0.1.0
 */
class Renderer final {
 private:
  SDL_Renderer* renderer = nullptr;
  Font_sptr font = nullptr;

 public:
  // TODO ctor with flags arg

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
  explicit Renderer(SDL_Window* window);

  static Renderer_uptr CreateUnique(SDL_Window* window);

  static Renderer_uptr CreateUnique(SDL_Renderer* renderer);

  ~Renderer();

  /**
   * Clears the rendering target with the currently selected color.
   *
   * @since 0.1.0
   */
  void Clear() noexcept;

  /**
   * Applies the previous rendering calls to the rendering target.
   *
   * @since 0.1.0
   */
  void Present() noexcept;

  /**
   * Renders a texture. This method has no effect if the supplied texture
   * pointer is null.
   *
   * @param texture a pointer to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @since 0.1.0
   */
  void RenderTexture(SDL_Texture* texture, int x, int y) noexcept;

  void RenderTexture(SDL_Texture* texture, float x, float y) noexcept;

  /**
   * Renders a texture. This method has no effect if the supplied texture
   * pointer is null OR if the supplied width and/or height isn't greater than
   * zero.
   *
   * @param texture a pointer to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @param width the width of the rendered texture.
   * @param height the height of the rendered texture.
   * @since 0.1.0
   */
  void RenderTexture(SDL_Texture* texture, int x, int y, int width,
                     int height) noexcept;

  /**
   * Renders a texture. This method has no effect if the supplied texture
   * pointer is null OR if the supplied width and/or height isn't greater than
   * zero.
   *
   * @param texture a pointer to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @param width the width of the rendered texture.
   * @param height the height of the rendered texture.
   * @since 0.1.0
   */
  void RenderTexture(SDL_Texture* texture, float x, float y, float width, float height) noexcept;

  void RenderTexture(SDL_Texture* texture,
                     const core::Rectangle& src,
                     const core::Rectangle& dst) noexcept;

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
  void RenderFillRect(int x, int y, int width, int height) noexcept;

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
  void RenderFillRect(float x, float y, float width, float height) noexcept;

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
  void RenderRect(float x, float y, float width, float height) noexcept;

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
  void RenderRect(int x, int y, int width, int height) noexcept;

  void RenderText(const std::string& text, float x, float y);

  /**
   * Sets the color that will be used by the renderer.
   *
   * @param red the red component value, in the range [0, 255].
   * @param green the green component value, in the range [0, 255].
   * @param blue the blue component value, in the range [0, 255].
   * @param alpha the alpha component value, in the range [0, 255].
   * @since 0.1.0
   */
  void SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) noexcept;

  /**
   * Sets the color that will be used by the renderer. This method will assume
   * that the desired color is fully opaque.
   *
   * @param red the red component value, in the range [0, 255].
   * @param green the green component value, in the range [0, 255].
   * @param blue the blue component value, in the range [0, 255].
   * @since 0.1.0
   */
  void SetColor(Uint8 red, Uint8 green, Uint8 blue) noexcept;

  void SetFont(Font_sptr font) noexcept;

  /**
   * Sets the viewport that will be used by the renderer.
   *
   * @param viewport the viewport that will be used by the renderer.
   * @since 0.1.0
   */
  void SetViewport(const core::Rectangle& viewport) noexcept;

  /**
   * Sets the viewport that will be used by the renderer. This method has no effect if any of the
   * arguments are less than or equal to zero.
   *
   * @param xScale the x-axis scale that will be used.
   * @param yScale the y-axis scale that will be used.
   * @since 0.1.0
   */
  void SetScale(float xScale, float yScale) noexcept;

  /**
   * Sets the logical dimensions of the renderer, which is useful for achieving
   * resolution-independent rendering. This method has no effect if either of the supplied
   * dimensions aren't greater than zero.
   *
   * @param width the logical width that will be used.
   * @param height the logical height that will be used.
   * @since 0.1.0
   */
  void SetLogicalSize(float width, float height) noexcept;

  /**
   * Sets whether or not to force integer scaling for the logical viewport. By default, this
   * property is set to false.
   *
   * @param useLogicalIntegerScale true if integer scaling should be used; false otherwise.
   * @since 0.1.0
   */
  void SetLogicalIntegerScale(bool useLogicalIntegerScale) noexcept;

  /**
   * Returns the logical width that the renderer uses.
   *
   * @return the logical width that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]] int GetLogicalWidth() const noexcept;

  /**
   * Returns the logical height that the renderer uses.
   *
   * @return the logical height that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]] int GetLogicalHeight() const noexcept;

  /**
   * Returns the x-axis scale that the renderer uses.
   *
   * @return the x-axis scale that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]] float GetXScale() const noexcept;

  /**
   * Returns the y-axis scale that the renderer uses.
   *
   * @return the y-axis scale that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]] float GetYScale() const noexcept;

  /**
   * Indicates whether or not the renderer uses integer scaling values for logical viewports. By
   * default, this property is set to false.
   *
   * @return true if the renderer uses integer scaling for logical viewports; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool GetUsingIntegerLogicalScaling() const noexcept;

  /**
   * Attempts to create and return a pointer to an SDL_Texture instance that represents the
   * supplied string rendered with the currently selected font. This method will not throw any
   * exception by itself, but dynamic memory allocation will occur behind-the-scenes.
   *
   * @param s the string that contains the content that will be rendered to a texture.
   * @returna a pointer to an SDL_Texture instance that represents the
   * supplied string rendered with the currently selected font; nullptr if the operation is
   * unsuccessful.
   */
  [[nodiscard]] SDL_Texture* CreateTexture(const std::string& s) const;

  /**
   * Returns the viewport that the renderer uses.
   *
   * @return the viewport that the renderer uses.
   * @since 0.1.0
   */
  [[nodiscard]] core::Rectangle GetViewport() const noexcept;

  /**
   * Returns a shared pointer to the internal font. The returned pointer might be null, if there
   * is no selected font.
   *
   * @return a shared pointer to the selected font; nullptr if there is no selected font.
   * @since 0.1.0
   */
  [[nodiscard]] inline Font_sptr GetFont() const noexcept {
    return font;
  }

  /**
   * Returns a pointer to the internal SDL_Renderer instance.
   *
   * @return a pointer to the internal SDL_Renderer instance.
   * @since 0.1.0
   */
  [[nodiscard]] inline SDL_Renderer* GetInternalRenderer() noexcept {
    return renderer;
  }
};

}
#pragma once
#include <SDL.h>
#include <SDL_image.h>

namespace wanderer::view {

/**
 * The Renderer class is a wrapper class for the SDL_Renderer struct.
 *
 * @see SDL_Renderer
 */
class Renderer final {
 private:
  SDL_Renderer* renderer = nullptr;

 public:
  /**
   * Creates a renderer based on the supplied SDL_Renderer.
   *
   * @param renderer a pointer to the SDL_Renderer that will be used by the
   * renderer. Note! The created renderer will take ownership of the supplied
   * pointer, and as such, will free it upon destruction.
   * @throws invalid_argument if the supplied pointer is null.
   * @since 0.1.0
   */
  Renderer(SDL_Renderer* renderer);

  /**
   * Creates a renderer based on the supplied SDL_Window.
   *
   * @param window a pointer to the SDL_Window that will be used to create the
   * renderer.
   * @throws invalid_argument if the supplied pointer is null.
   * @since 0.1.0
   */
  Renderer(SDL_Window* window);

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
   * Renders a filled rect with the currently selected color.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 0.1.0
   */
  void RenderFillRect(int x, int y, int width, int height) noexcept;

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
};

}  // namespace wanderer::view
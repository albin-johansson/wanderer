#pragma once
#include <SDL_render.h>
#include <string>

namespace wanderer::visuals {

/**
 * The Image class represents an image that is hardware-accelerated.
 *
 * @see SDL_Texture
 * @since 0.1.0
 */
class Image final {
 private:
  SDL_Texture* texture = nullptr;

 public:
  /**
   * @param renderer a pointer to the SDL_Renderer used to create the image.
   * @param path the file path of the image that will be loaded.
   * @throws NullPointerException if the supplied renderer pointer is null.
   * @throws BadStateException if the image cannot be loaded.
   * @since 0.1.0
   */
  Image(SDL_Renderer* renderer, const std::string& path);

  ~Image();

  /**
   * Returns the format of the internal SDL_Texture.
   *
   * @return the format of the internal SDL_Texture.
   * @since 0.1.0
   */
  [[nodiscard]] Uint32 GetFormat() const noexcept; // TODO check

  /**
   * Returns the texture access of the internal SDL_Texture.
   *
   * @return the texture access of the internal SDL_Texture.
   * @since 0.1.0
   */
  [[nodiscard]] int GetAccess() const noexcept; // TODO check

  /**
   * Returns the width of the image.
   *
   * @return the width of the image.
   * @since 0.1.0
   */
  [[nodiscard]] int GetWidth() const noexcept;

  /**
   * Returns the height of the image.
   *
   * @return the height of the image.
   * @since 0.1.0
   */
  [[nodiscard]] int GetHeight() const noexcept;

  /**
   * Returns a pointer to the internal SDL_Texture of the image.
   *
   * @return a pointer to the internal SDL_Texture of the image.
   * @since 0.1.0
   */
  [[nodiscard]] inline SDL_Texture* GetTexture() noexcept {
    return texture;
  }
};

}

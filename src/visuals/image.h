#pragma once
#include <string>
#include <cstdint>
#include <SDL_render.h>

namespace albinjohansson::wanderer {

/**
 * The Image class represents an image that is hardware-accelerated. Instances of the Image class
 * can be converted to std::string (explicitly using static_cast) and SDL_Texture* (implicitly).
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

  Image(SDL_Texture* texture);

  Image(SDL_Renderer* renderer, SDL_Surface* surface);

  ~Image();

  /**
   * Returns the format of the internal SDL_Texture.
   *
   * @return the format of the internal SDL_Texture.
   * @since 0.1.0
   */
  [[nodiscard]]
  uint32_t GetFormat() const noexcept; // TODO check

  /**
   * Returns the texture access of the internal SDL_Texture.
   *
   * @return the texture access of the internal SDL_Texture.
   * @since 0.1.0
   */
  [[nodiscard]]
  int GetAccess() const noexcept; // TODO check

  /**
   * Returns the width of the image.
   *
   * @return the width of the image.
   * @since 0.1.0
   */
  [[nodiscard]]
  int GetWidth() const noexcept;

  /**
   * Returns the height of the image.
   *
   * @return the height of the image.
   * @since 0.1.0
   */
  [[nodiscard]]
  int GetHeight() const noexcept;

  /**
   * Returns a pointer to the internal SDL_Texture of the image.
   *
   * @return a pointer to the internal SDL_Texture of the image.
   * @since 0.1.0
   */
  [[nodiscard]]
  SDL_Texture* GetTexture() noexcept;

  /**
   * Returns a string representation of the image.
   *
   * @return a string representation of the image.
   * @since 0.1.0
   */
  [[nodiscard]]
  std::string ToString() const;

  /**
   * Returns a string representation of the image.
   *
   * @return a string representation of the image.
   * @since 0.1.0
   */
  explicit operator std::string();

  /**
   * Returns a pointer to the internal SDL_Texture.
   *
   * @return a pointer to the internal SDL_Texture.
   * @since 0.1.0
   */
  operator SDL_Texture*() const noexcept;
};

}

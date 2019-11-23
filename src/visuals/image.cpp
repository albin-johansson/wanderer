#include "image.h"
#include "objects.h"
#include <SDL_image.h>
#include "bad_state_exception.h"

namespace albinjohansson::wanderer {

Image::Image(SDL_Renderer* renderer, const std::string& path) {
  Objects::RequireNonNull(renderer);
  texture = IMG_LoadTexture(renderer, path.c_str());
  if (texture == nullptr) {
    throw BadStateException();
  }
}

Image::Image(SDL_Texture* texture) {
  this->texture = Objects::RequireNonNull(texture);
}

Image::~Image() {
  SDL_DestroyTexture(texture);
}

Image_uptr Image::Create(SDL_Renderer* renderer, const std::string& path) {
  return std::make_unique<Image>(renderer, path);
}

Image_uptr Image::Create(SDL_Texture* texture) {
  return std::make_unique<Image>(texture);
}

Uint32 Image::GetFormat() const noexcept {
  Uint32 format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);
  return format;
}

int Image::GetAccess() const noexcept {
  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);
  return access;
}

int Image::GetWidth() const noexcept {
  int width = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
  return width;
}

int Image::GetHeight() const noexcept {
  int height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &height);
  return height;
}

}
#include "renderer.h"
#include "objects.h"

using namespace wanderer::core;

namespace wanderer::visuals {

Renderer::Renderer(SDL_Renderer* renderer) {
  this->renderer = Objects::RequireNonNull(renderer);
}

Renderer::Renderer(SDL_Window* window) {
  Objects::RequireNonNull(window);
  Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  renderer = SDL_CreateRenderer(window, -1, flags);
}

Renderer::~Renderer() {
  if (renderer != nullptr) {
    SDL_DestroyRenderer(renderer);
  }
}

void Renderer::Clear() noexcept { SDL_RenderClear(renderer); }

void Renderer::Present() noexcept { SDL_RenderPresent(renderer); }

void Renderer::RenderTexture(SDL_Texture* texture, int x, int y) noexcept {
  if (texture != nullptr) {
    int width = 0;
    int height = 0;

    // TODO check if OK
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
  }
}

void Renderer::RenderTexture(SDL_Texture* texture, int x, int y, int width,
                             int height) noexcept {
  if ((texture != nullptr) && (width > 0) && (height > 0)) {
    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
  }
}

void Renderer::RenderTexture(SDL_Texture* texture,
                             float x,
                             float y,
                             int width,
                             int height) noexcept {
  if ((texture != nullptr) && (width > 0) && (height > 0)) {
    SDL_FRect dst = {x, y, static_cast<float>(width), static_cast<float>(height)};
    SDL_RenderCopyF(renderer, texture, nullptr, &dst);
  }
}

void Renderer::RenderFillRect(float x, float y, int width, int height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_FRect rect = {x, y, static_cast<float>(width), static_cast<float>(height)};
    SDL_RenderFillRectF(renderer, &rect);
  }
}

void Renderer::RenderFillRect(int x, int y, int width, int height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
  }
}

void Renderer::RenderRect(float x, float y, int width, int height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_FRect rect = {x, y, static_cast<float>(width), static_cast<float>(height)};
    SDL_RenderDrawRectF(renderer, &rect);
  }
}

void Renderer::RenderRect(int x, int y, int width, int height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(renderer, &rect);
  }
}

void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue,
                        Uint8 alpha) noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue) noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
}

}  // namespace wanderer::visuals
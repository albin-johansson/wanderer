#include "renderer.h"
#include <stdexcept>

namespace wanderer::view {

Renderer::Renderer(SDL_Renderer* renderer) {
  if (renderer == nullptr) {
    throw std::invalid_argument("Null renderer!");
  }
  this->renderer = renderer;
}

Renderer::Renderer(SDL_Window* window) {
  if (window == nullptr) {
    throw std::invalid_argument("Null window!");
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

void Renderer::RenderFillRect(int x, int y, int width, int height) noexcept {
  SDL_Rect rect = {x, y, width, height};
  SDL_RenderFillRect(renderer, &rect);
}

void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue,
                        Uint8 alpha) noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue) noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
}

}  // namespace wanderer::view
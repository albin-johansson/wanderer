#include "renderer.h"
#include "objects.h"
#include "bool_converter.h"
#include <SDL_log.h>

#include <utility>

using namespace wanderer::core;
using namespace wanderer::service;

namespace wanderer::visuals {

Renderer::Renderer(SDL_Renderer* renderer) {
  this->renderer = Objects::RequireNonNull(renderer);
  SetLogicalIntegerScale(false);
}

Renderer::Renderer(SDL_Window* window) {
  Objects::RequireNonNull(window);
  Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  renderer = SDL_CreateRenderer(window, -1, flags);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SetLogicalIntegerScale(false);
}

Renderer::~Renderer() {
  if (renderer != nullptr) {
    SDL_DestroyRenderer(renderer);
  }
}

Renderer_uptr Renderer::Create(SDL_Renderer* renderer) {
  return std::make_unique<Renderer>(renderer);
}

Renderer_uptr Renderer::Create(SDL_Window* window) {
  return std::make_unique<Renderer>(window);
}

void Renderer::Clear() noexcept { SDL_RenderClear(renderer); }

void Renderer::Present() noexcept { SDL_RenderPresent(renderer); }

void Renderer::RenderTexture(SDL_Texture* texture, int x, int y) noexcept {
  if (texture != nullptr) {
    int width = 0;
    int height = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
  }
}

void Renderer::RenderTexture(SDL_Texture* texture, float x, float y) noexcept {
  if (texture != nullptr) {
    int width = 0;
    int height = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SDL_FRect dst = {x, y, static_cast<float>(width), static_cast<float>(height)};
    SDL_RenderCopyF(renderer, texture, nullptr, &dst);
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
                             float width,
                             float height) noexcept {
  if ((texture != nullptr) && (width > 0) && (height > 0)) {
    SDL_FRect dst = {x, y, width, height};
    SDL_RenderCopyF(renderer, texture, nullptr, &dst);
  }
}

void Renderer::RenderTexture(SDL_Texture* texture,
                             const core::Rectangle& s,
                             const core::Rectangle& d) noexcept {
  if (texture != nullptr) {
    SDL_Rect src = s.ToSdlRect();
    SDL_FRect dst = {d.GetX(), d.GetY(), d.GetWidth(), d.GetHeight()};
    SDL_RenderCopyF(renderer, texture, &src, &dst);
  }
}

void Renderer::RenderFillRect(float x, float y, float width, float height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_FRect rect = {x, y, width, height};
    SDL_RenderFillRectF(renderer, &rect);
  }
}

void Renderer::RenderFillRect(int x, int y, int width, int height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
  }
}

void Renderer::RenderRect(float x, float y, float width, float height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_FRect rect = {x, y, width, height};
    SDL_RenderDrawRectF(renderer, &rect);
  }
}

void Renderer::RenderRect(int x, int y, int width, int height) noexcept {
  if ((width > 0) && (height > 0)) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(renderer, &rect);
  }
}

void Renderer::RenderText(const std::string& text, float x, float y) {
  if (font != nullptr && !text.empty()) {
    SDL_Texture* texture = CreateTexture(text);

    if (texture == nullptr) {
      return;
    }

    RenderTexture(texture, x, y);
    SDL_DestroyTexture(texture);
  }
}

void Renderer::RenderText(const std::string& text, float x, float y, Font& font) {
  if (!text.empty()) {
    SDL_Texture* texture = CreateTexture(text, font);

    if (texture == nullptr) {
      return;
    }

    RenderTexture(texture, x, y);
    SDL_DestroyTexture(texture);
  }
}

void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue) noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
}

void Renderer::SetFont(Font_sptr font) noexcept {
  this->font = std::move(font);
}

void Renderer::SetViewport(const core::Rectangle& viewport) noexcept {
  SDL_Rect rect = viewport.ToSdlRect();
  SDL_RenderSetViewport(renderer, &rect);
}

void Renderer::SetScale(float xScale, float yScale) noexcept {
  if ((xScale > 0) && (yScale > 0)) {
    SDL_RenderSetScale(renderer, xScale, yScale);
  }
}

void Renderer::SetLogicalSize(float width, float height) noexcept {
  if ((width > 0) && (height > 0)) {
    int result = SDL_RenderSetLogicalSize(renderer,
                                          static_cast<int>(width),
                                          static_cast<int>(height));
    if (result != 0) {
      SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                     SDL_LOG_PRIORITY_WARN,
                     "Failed to set logical size! %s",
                     SDL_GetError());
    }
  }
}

void Renderer::SetLogicalIntegerScale(bool useLogicalIntegerScale) noexcept {
  SDL_RenderSetIntegerScale(renderer, BoolConverter::Convert(useLogicalIntegerScale));
}

int Renderer::GetLogicalWidth() const noexcept {
  int w = 0;
  SDL_RenderGetLogicalSize(renderer, &w, nullptr);
  return w;
}

int Renderer::GetLogicalHeight() const noexcept {
  int h = 0;
  SDL_RenderGetLogicalSize(renderer, nullptr, &h);
  return h;
}

float Renderer::GetXScale() const noexcept {
  float xScale = 0;
  SDL_RenderGetScale(renderer, &xScale, nullptr);
  return xScale;
}

float Renderer::GetYScale() const noexcept {
  float yScale = 0;
  SDL_RenderGetScale(renderer, nullptr, &yScale);
  return yScale;
}

Rectangle Renderer::GetViewport() const noexcept {
  SDL_Rect viewport = {0, 0, 0, 0};
  SDL_RenderGetViewport(renderer, &viewport);
  return Rectangle(static_cast<float>(viewport.x),
                   static_cast<float>(viewport.y),
                   static_cast<float>(viewport.w),
                   static_cast<float>(viewport.h));
}

bool Renderer::GetUsingIntegerLogicalScaling() const noexcept {
  return SDL_RenderGetIntegerScale(renderer);
}

SDL_Texture* Renderer::CreateTexture(const std::string& s) const {
  if (font == nullptr) {
    return nullptr;
  } else {
    return CreateTexture(s, *font);
  }
}

SDL_Texture* Renderer::CreateTexture(const std::string& s, Font& font) const {
  if (s.empty()) {
    return nullptr;
  }

  Uint8 r = 0, g = 0, b = 0, a = 0;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  SDL_Color color = {r, g, b, a};
  SDL_Surface* surface = TTF_RenderText_Blended(font.GetInternalFont(), s.c_str(), color);

  if (surface == nullptr) {
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}

}  // namespace wanderer::visuals
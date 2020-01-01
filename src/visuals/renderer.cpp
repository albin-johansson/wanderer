#include "renderer.h"
#include "image.h"
#include "font.h"
#include "require.h"
#include "bool_converter.h"
#include "math_utils.h"
#include <SDL_log.h>

namespace albinjohansson::wanderer {

Renderer::Renderer(SDL_Renderer* renderer) {
  this->renderer = Require::NotNull(renderer);
  SetLogicalIntegerScale(false);
}

Renderer::Renderer(SDL_Window* window, uint32_t flags) {
  Require::NotNull(window);

  renderer = SDL_CreateRenderer(window, -1, flags);

  SetBlendMode(SDL_BLENDMODE_BLEND);
  SetLogicalIntegerScale(false);
}

Renderer::~Renderer() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
}

void Renderer::Clear() const noexcept {
  SDL_RenderClear(renderer);
}

void Renderer::Present() const noexcept {
  SDL_RenderPresent(renderer);
}

void Renderer::RenderTexture(const Image& texture, int x, int y) const noexcept {
  SDL_Rect dst = {x, y, texture.GetWidth(), texture.GetHeight()};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void Renderer::RenderTexture(const Image& texture, float x, float y) const noexcept {
  SDL_FRect dst = {x,
                   y,
                   static_cast<float>(texture.GetWidth()),
                   static_cast<float>(texture.GetHeight())};
  SDL_RenderCopyF(renderer, texture, nullptr, &dst);
}

void Renderer::RenderTexture(const Image& texture,
                             int x,
                             int y,
                             int width,
                             int height) const noexcept {
  SDL_Rect dst = {x, y, width, height};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void Renderer::RenderTexture(const Image& texture,
                             float x,
                             float y,
                             float width,
                             float height) const noexcept {
  SDL_FRect dst = {x, y, width, height};
  SDL_RenderCopyF(renderer, texture, nullptr, &dst);
}

void Renderer::RenderTexture(const Image& texture,
                             const Rectangle& source,
                             const FRectangle& destination) const noexcept {
  SDL_Rect src = source;
  SDL_FRect dst = destination;
  SDL_RenderCopyF(renderer, texture, &src, &dst);
}

void Renderer::RenderTextureTranslated(const Image& texture,
                                       const Rectangle& source,
                                       const FRectangle& destination) const noexcept {
  SDL_Rect src = source;
  SDL_FRect dst = destination;

  dst.x = translationViewport.GetTranslatedX(dst.x);
  dst.y = translationViewport.GetTranslatedY(dst.y);

  SDL_RenderCopyF(renderer, texture, &src, &dst);
}

void Renderer::RenderFillRect(float x, float y, float width, float height) const noexcept {
  SDL_FRect rect = {x, y, width, height};
  SDL_RenderFillRectF(renderer, &rect);
}

void Renderer::RenderFillRect(int x, int y, int width, int height) const noexcept {
  SDL_Rect rect = {x, y, width, height};
  SDL_RenderFillRect(renderer, &rect);
}

void Renderer::RenderRect(float x, float y, float width, float height) const noexcept {
  SDL_FRect rect = {x, y, width, height};
  SDL_RenderDrawRectF(renderer, &rect);
}

void Renderer::RenderRect(int x, int y, int width, int height) const noexcept {
  SDL_Rect rect = {x, y, width, height};
  SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::RenderText(const std::string& text, float x, float y, const Font& font) const {
  if (!text.empty()) {
    auto texture = CreateTexture(text, font);

    if (!texture) {
      return;
    }

    RenderTexture(*texture, x, y);
  }
}

void Renderer::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::SetViewport(const FRectangle& viewport) noexcept {
  auto rect = static_cast<SDL_Rect>(viewport);
  SDL_RenderSetViewport(renderer, &rect);
}

void Renderer::SetTranslationViewport(const Viewport& viewport) noexcept {
  translationViewport = viewport;
}

void Renderer::SetBlendMode(const SDL_BlendMode& blendMode) noexcept {
  SDL_SetRenderDrawBlendMode(renderer, blendMode);
}

void Renderer::SetScale(float xScale, float yScale) noexcept {
  SDL_RenderSetScale(renderer, xScale, yScale);
}

void Renderer::SetLogicalSize(float width, float height) noexcept {
  int result = SDL_RenderSetLogicalSize(renderer,
                                        MathUtils::Round(width),
                                        MathUtils::Round(height));
  if (result != 0) {
    SDL_Log("Failed to set logical size! %s", SDL_GetError());
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

FRectangle Renderer::GetViewport() const noexcept {
  SDL_Rect viewport = {0, 0, 0, 0};
  SDL_RenderGetViewport(renderer, &viewport);
  return viewport;
}

const Viewport& Renderer::GetTranslationViewport() const noexcept {
  return translationViewport;
}

bool Renderer::GetUsingIntegerLogicalScaling() const noexcept {
  return SDL_RenderGetIntegerScale(renderer);
}

std::unique_ptr<Image> Renderer::CreateTexture(const std::string& s, const Font& font) const {
  if (s.empty()) {
    return nullptr;
  }

  uint8_t r = 0, g = 0, b = 0, a = 0;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  SDL_Color color = {r, g, b, a};
  SDL_Surface* surface = TTF_RenderText_Blended(font, s.c_str(), color);

  if (!surface) {
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return std::make_unique<Image>(texture);
}

SDL_Renderer* Renderer::GetInternalRenderer() noexcept {
  return renderer;
}

Renderer::operator SDL_Renderer*() const noexcept {
  return renderer;
}

}
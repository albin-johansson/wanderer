#include "renderer.h"
#include "image.h"
#include "font.h"
#include "require.h"
#include "bool_converter.h"
#include "math_utils.h"
#include <SDL_log.h>

using namespace albinjohansson::wanderer;

namespace centurion {

Renderer::Renderer(SDL_Renderer* renderer) {
  this->renderer = Require::not_null(renderer);
  set_logical_integer_scale(false);
}

Renderer::Renderer(SDL_Window* window, uint32_t flags) {
  Require::not_null(window);

  renderer = SDL_CreateRenderer(window, -1, flags);

  set_blend_mode(SDL_BLENDMODE_BLEND);
  set_logical_integer_scale(false);
}

Renderer::~Renderer() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
}

void Renderer::clear() const noexcept {
  SDL_RenderClear(renderer);
}

void Renderer::present() const noexcept {
  SDL_RenderPresent(renderer);
}

void Renderer::draw_image(const Image& texture, int x, int y) const noexcept {
  const SDL_Rect dst{x, y, texture.get_width(), texture.get_height()};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void Renderer::draw_image(const Image& texture, float x, float y) const noexcept {
  const SDL_FRect dst{x, y,
                      static_cast<float>(texture.get_width()),
                      static_cast<float>(texture.get_height())};
  SDL_RenderCopyF(renderer, texture, nullptr, &dst);
}

void Renderer::draw_image(const Image& texture,
                          int x,
                          int y,
                          int width,
                          int height) const noexcept {
  const SDL_Rect dst{x, y, width, height};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void Renderer::draw_image(const Image& texture,
                          float x,
                          float y,
                          float width,
                          float height) const noexcept {
  const SDL_FRect dst{x, y, width, height};
  SDL_RenderCopyF(renderer, texture, nullptr, &dst);
}

void Renderer::draw_image(const Image& texture,
                          const Rectangle& source,
                          const FRectangle& destination) const noexcept {
  const SDL_Rect src = source;
  const SDL_FRect dst = destination;
  SDL_RenderCopyF(renderer, texture, &src, &dst);
}

void Renderer::draw_image_translated(const Image& texture,
                                     const Rectangle& source,
                                     const FRectangle& destination) const noexcept {
  const SDL_Rect src = source;
  SDL_FRect dst = destination;

  dst.x = translationViewport.get_translated_x(dst.x);
  dst.y = translationViewport.get_translated_y(dst.y);

  SDL_RenderCopyF(renderer, texture, &src, &dst);
}

void Renderer::fill_rect(float x, float y, float width, float height) const noexcept {
  const SDL_FRect rect{x, y, width, height};
  SDL_RenderFillRectF(renderer, &rect);
}

void Renderer::fill_rect(int x, int y, int width, int height) const noexcept {
  const SDL_Rect rect{x, y, width, height};
  SDL_RenderFillRect(renderer, &rect);
}

void Renderer::draw_rect(float x, float y, float width, float height) const noexcept {
  const SDL_FRect rect{x, y, width, height};
  SDL_RenderDrawRectF(renderer, &rect);
}

void Renderer::draw_rect(int x, int y, int width, int height) const noexcept {
  const SDL_Rect rect{x, y, width, height};
  SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::draw_text(const std::string& text, float x, float y, const Font& font) const {
  if (!text.empty()) {
    const auto texture = create_image(text, font);

    if (!texture) {
      return;
    }

    draw_image(*texture, x, y);
  }
}

void Renderer::set_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) const noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::set_viewport(const FRectangle& viewport) noexcept {
  const auto rect = static_cast<SDL_Rect>(viewport);
  SDL_RenderSetViewport(renderer, &rect);
}

void Renderer::set_translation_viewport(const Viewport& viewport) noexcept {
  translationViewport = viewport;
}

void Renderer::set_blend_mode(const SDL_BlendMode& blendMode) noexcept {
  SDL_SetRenderDrawBlendMode(renderer, blendMode);
}

void Renderer::set_scale(float xScale, float yScale) noexcept {
  if (xScale > 0 && yScale > 0) {
    SDL_RenderSetScale(renderer, xScale, yScale);
  }
}

void Renderer::set_logical_size(float width, float height) noexcept {
  if (width > 0 && height > 0) {
    const int result = SDL_RenderSetLogicalSize(renderer,
                                                MathUtils::round(width),
                                                MathUtils::round(height));
    if (result != 0) {
      SDL_Log("Failed to set logical size! %s", SDL_GetError());
    }
  }
}

void Renderer::set_logical_integer_scale(bool useLogicalIntegerScale) noexcept {
  SDL_RenderSetIntegerScale(renderer, BoolConverter::convert(useLogicalIntegerScale));
}

int Renderer::get_logical_width() const noexcept {
  int w = 0;
  SDL_RenderGetLogicalSize(renderer, &w, nullptr);
  return w;
}

int Renderer::get_logical_height() const noexcept {
  int h = 0;
  SDL_RenderGetLogicalSize(renderer, nullptr, &h);
  return h;
}

float Renderer::get_x_scale() const noexcept {
  float xScale = 0;
  SDL_RenderGetScale(renderer, &xScale, nullptr);
  return xScale;
}

float Renderer::get_y_scale() const noexcept {
  float yScale = 0;
  SDL_RenderGetScale(renderer, nullptr, &yScale);
  return yScale;
}

FRectangle Renderer::get_viewport() const noexcept {
  SDL_Rect viewport{0, 0, 0, 0};
  SDL_RenderGetViewport(renderer, &viewport);
  return viewport;
}

const Viewport& Renderer::get_translation_viewport() const noexcept {
  return translationViewport;
}

bool Renderer::is_using_integer_logical_scaling() const noexcept {
  return SDL_RenderGetIntegerScale(renderer);
}

std::unique_ptr<Image> Renderer::create_image(const std::string& s, const Font& font) const {
  if (s.empty()) {
    return nullptr;
  }

  uint8_t r = 0, g = 0, b = 0, a = 0;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  const SDL_Color color{r, g, b, a};
  SDL_Surface* surface = TTF_RenderText_Blended(font, s.c_str(), color);

  if (!surface) {
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return std::make_unique<Image>(texture);
}

Renderer::operator SDL_Renderer*() const noexcept {
  return renderer;
}

}
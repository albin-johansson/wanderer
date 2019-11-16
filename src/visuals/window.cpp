#include "window.h"
#include <stdexcept>
#include "objects.h"
#include "bool_converter.h"

using namespace wanderer::core;
using namespace wanderer::service;

namespace wanderer::visuals {

Window::Window(const std::string& title, int width, int height) {
  if ((width < 1) || (height < 1)) {
    throw std::invalid_argument("Invalid width or height!");
  }

  auto pos = SDL_WINDOWPOS_CENTERED;
  window = SDL_CreateWindow(title.c_str(), pos, pos, width, height,
                            SDL_WINDOW_HIDDEN);
}

Window::~Window() {
  if (window != nullptr) {
    SDL_DestroyWindow(window);
  }
}

Window_uptr Window::Create(const std::string& title, int width, int height) {
  return std::make_unique<Window>(title, width, height);
}

void Window::Show() noexcept { SDL_ShowWindow(window); }

void Window::Hide() noexcept { SDL_HideWindow(window); }

void Window::SetFullscreen(bool fullscreen) noexcept {
  Uint32 flags = SDL_GetWindowFlags(window);
  flags = (fullscreen) ? (flags | SDL_WINDOW_FULLSCREEN)
                       : (flags & ~SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(window, flags);
}

void Window::SetResizable(bool isResizable) noexcept {
  SDL_SetWindowResizable(window, BoolConverter::Convert(isResizable));
}

void Window::SetWidth(int width) {
  if (width < 1) {
    throw std::invalid_argument("Invalid width!");
  } else {
    SDL_SetWindowSize(window, width, GetHeight());
  }
}

void Window::SetHeight(int height) {
  if (height < 1) {
    throw std::invalid_argument("Invalid height!");
  } else {
    SDL_SetWindowSize(window, GetWidth(), height);
  }
}

void Window::SetIcon(SDL_Surface* icon) {
  Objects::RequireNonNull(icon);
  SDL_SetWindowIcon(window, icon);
}

bool Window::IsResizable() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE;
}

bool Window::IsFullscreen() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
}

bool Window::IsVisible() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
}

int Window::GetWidth() const noexcept {
  int width = 0;
  SDL_GetWindowSize(window, &width, nullptr);

  return width;
}

int Window::GetHeight() const noexcept {
  int height = 0;
  SDL_GetWindowSize(window, nullptr, &height);

  return height;
}

}  // namespace wanderer::visuals
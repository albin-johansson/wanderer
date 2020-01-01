#include "window.h"
#include "window_listener.h"
#include "require.h"
#include "bool_converter.h"
#include <stdexcept>
#include <cstdint>

namespace albinjohansson::wanderer {

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

void Window::NotifyWindowListeners() noexcept {
  const auto& self = *this;
  for (auto listener : windowListeners) {
    if (listener) {
      listener->WindowUpdated(self); // FIXME not noexcept
    }
  }
}

void Window::Show() noexcept {
  SDL_ShowWindow(window);
  NotifyWindowListeners();
}

void Window::Hide() noexcept {
  SDL_HideWindow(window);
  NotifyWindowListeners();
}

void Window::AddWindowListener(IWindowListener* listener) noexcept {
  if (listener) {
    windowListeners.push_back(listener);
  }
}

void Window::SetFullscreen(bool fullscreen) noexcept {
  uint32_t flags = SDL_GetWindowFlags(window);
  flags = (fullscreen) ? (flags | SDL_WINDOW_FULLSCREEN)
                       : (flags & ~SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(window, flags);
  NotifyWindowListeners();
}

void Window::SetResizable(bool isResizable) noexcept {
  SDL_SetWindowResizable(window, BoolConverter::Convert(isResizable));
  NotifyWindowListeners();
}

void Window::SetWidth(int width) {
  if (width < 1) {
    throw std::invalid_argument("Invalid width!");
  } else {
    SDL_SetWindowSize(window, width, GetHeight());
    NotifyWindowListeners();
  }
}

void Window::SetHeight(int height) {
  if (height < 1) {
    throw std::invalid_argument("Invalid height!");
  } else {
    SDL_SetWindowSize(window, GetWidth(), height);
    NotifyWindowListeners();
  }
}

void Window::SetIcon(SDL_Surface* icon) {
  Require::NotNull(icon);
  SDL_SetWindowIcon(window, icon);
  NotifyWindowListeners();
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

std::string Window::GetTitle() const noexcept {
  return SDL_GetWindowTitle(window);
}

SDL_Window* Window::GetInternalWindow() noexcept {
  return window;
}

Window::operator SDL_Window*() const noexcept {
  return window;
}

}
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

  const auto pos = SDL_WINDOWPOS_CENTERED;
  window = SDL_CreateWindow(title.c_str(), pos, pos, width, height,
                            SDL_WINDOW_HIDDEN);
}

Window::~Window() {
  if (window) {
    SDL_DestroyWindow(window);
  }
}

void Window::notify_window_listeners() noexcept {
  const auto& self = *this;
  for (auto listener : windowListeners) {
    if (listener) {
      listener->WindowUpdated(self); // FIXME not noexcept
    }
  }
}

void Window::show() noexcept {
  SDL_ShowWindow(window);
  notify_window_listeners();
}

void Window::hide() noexcept {
  SDL_HideWindow(window);
  notify_window_listeners();
}

void Window::add_window_listener(IWindowListener* listener) noexcept {
  if (listener) {
    windowListeners.push_back(listener);
  }
}

void Window::set_fullscreen(bool fullscreen) noexcept {
  uint32_t flags = SDL_GetWindowFlags(window);
  flags = (fullscreen) ? (flags | SDL_WINDOW_FULLSCREEN)
                       : (flags & ~SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(window, flags);
  notify_window_listeners();
}

void Window::set_resizable(bool isResizable) noexcept {
  SDL_SetWindowResizable(window, BoolConverter::Convert(isResizable));
  notify_window_listeners();
}

void Window::set_width(int width) {
  if (width < 1) {
    throw std::invalid_argument("Invalid width!");
  } else {
    SDL_SetWindowSize(window, width, get_height());
    notify_window_listeners();
  }
}

void Window::set_height(int height) {
  if (height < 1) {
    throw std::invalid_argument("Invalid height!");
  } else {
    SDL_SetWindowSize(window, get_width(), height);
    notify_window_listeners();
  }
}

void Window::set_icon(SDL_Surface* icon) {
  Require::NotNull(icon);
  SDL_SetWindowIcon(window, icon);
  notify_window_listeners();
}

bool Window::is_resizable() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE;
}

bool Window::is_fullscreen() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
}

bool Window::is_visible() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
}

int Window::get_width() const noexcept {
  int width = 0;
  SDL_GetWindowSize(window, &width, nullptr);

  return width;
}

int Window::get_height() const noexcept {
  int height = 0;
  SDL_GetWindowSize(window, nullptr, &height);

  return height;
}

std::string Window::get_title() const noexcept {
  return SDL_GetWindowTitle(window);
}

Window::operator SDL_Window*() const noexcept {
  return window;
}

}
#include "catch.hpp"
#include "window.h"

using namespace wanderer::visuals;

TEST_CASE("WindowCtor", "[Window]") {
  CHECK_THROWS_AS(Window("", 0, 10), std::invalid_argument);
  CHECK_THROWS_AS(Window("", 10, 0), std::invalid_argument);

  int width = 123;
  int height = 321;
  Window window("Foo", width, height); // TODO test title

  CHECK(window.GetWidth() == width);
  CHECK(window.GetHeight() == height);
}

TEST_CASE("Window::Show", "[Window]") {
  Window window("Foo", 100, 100);

  window.Show();
  CHECK(window.IsVisible());
}

TEST_CASE("Window::Hide", "[Window]") {
  Window window("Foo", 100, 100);

  window.Hide();
  CHECK(!window.IsVisible());
}

TEST_CASE("Window::SetFullscreen", "[Window]") {
  Window window("Foo", 100, 100);

  window.SetFullscreen(true);
  CHECK(window.IsFullscreen());

  window.SetFullscreen(false);
  CHECK(!window.IsFullscreen());
}

TEST_CASE("Window::SetResizable", "[Window]") {
  Window window("Foo", 100, 100);

  window.SetResizable(true);
  CHECK(window.IsResizable());

  window.SetResizable(false);
  CHECK(!window.IsResizable());
}

TEST_CASE("Window::SetWidth", "[Window]") {
  Window window("Foo", 100, 100);

  int width = 812;
  window.SetWidth(width);
  CHECK(window.GetWidth() == width);
}

TEST_CASE("Window::SetHeight", "[Window]") {
  Window window("Foo", 100, 100);

  int height = 327;
  window.SetHeight(height);
  CHECK(window.GetHeight() == height);
}

TEST_CASE("Window::GetInternalWindow", "[Window]") {
  Window window("Foo", 100, 100);
  SDL_Window* sdlWindow = window.GetInternalWindow();
  CHECK(sdlWindow != nullptr);
}
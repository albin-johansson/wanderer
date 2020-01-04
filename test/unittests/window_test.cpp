#include "catch.hpp"
#include "window.h"
#include <memory>

using namespace albinjohansson::wanderer;

TEST_CASE("Window(string, int, int)", "[Window]") {
  CHECK_THROWS_AS(Window("", 0, 10), std::invalid_argument);
  CHECK_THROWS_AS(Window("", 10, 0), std::invalid_argument);

  int width = 123;
  int height = 321;
  Window window("Foo", width, height); // TODO test title

  CHECK(window.get_width() == width);
  CHECK(window.get_height() == height);
}

TEST_CASE("Window::Create", "[Window]") {
  CHECK_THROWS_AS(std::make_unique<Window>("", 0, 1), std::invalid_argument);
  CHECK_THROWS_AS(std::make_unique<Window>("", 1, 0), std::invalid_argument);

  auto title = "Foo";
  int width = 831;
  int height = 351;
  auto window = std::make_unique<Window>(title, width, height);

  CHECK(window->get_title() == title);
  CHECK(window->get_width() == width);
  CHECK(window->get_height() == height);
}

TEST_CASE("Window::Show", "[Window]") {
  Window window("Foo", 100, 100);

  window.show();
  CHECK(window.is_visible());
}

TEST_CASE("Window::Hide", "[Window]") {
  Window window("Foo", 100, 100);

  window.hide();
  CHECK(!window.is_visible());
}

TEST_CASE("Window::SetFullscreen", "[Window]") {
  Window window("Foo", 100, 100);

  window.set_fullscreen(true);
  CHECK(window.is_fullscreen());

  window.set_fullscreen(false);
  CHECK(!window.is_fullscreen());
}

TEST_CASE("Window::SetResizable", "[Window]") {
  Window window("Foo", 100, 100);

  window.set_resizable(true);
  CHECK(window.is_resizable());

  window.set_resizable(false);
  CHECK(!window.is_resizable());
}

TEST_CASE("Window::SetWidth", "[Window]") {
  Window window("Foo", 100, 100);

  int width = 812;
  window.set_width(width);
  CHECK(window.get_width() == width);
}

TEST_CASE("Window::SetHeight", "[Window]") {
  Window window("Foo", 100, 100);

  int height = 327;
  window.set_height(height);
  CHECK(window.get_height() == height);
}

TEST_CASE("Window::GetTitle", "[Window]") {
  auto title = "HelloWorld";
  Window window(title, 100, 100);
  CHECK(window.get_title() == title);
}
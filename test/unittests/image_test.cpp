#include "catch.hpp"
#include "image.h"
#include "window.h"
#include "renderer.h"
#include "require.h"
#include "bad_state_exception.h"

using namespace albinjohansson::wanderer;

TEST_CASE("Image(string)", "[Image]") {
  Window window("foo", 10, 10);
  Renderer renderer(window);

  CHECK_THROWS_AS(Image(nullptr, ""), Require::NullPointerException);
  CHECK_THROWS_AS(Image(renderer, "badpath"), BadStateException);

  Image img(renderer, "resources/img/grass.png");

  // The grass.png image is 108x108
  CHECK(img.GetWidth() == 108);
  CHECK(img.GetHeight() == 108);
}

TEST_CASE("Image::GetFormat", "[Image]") {
  Window window("foo", 10, 10);
  Renderer renderer(window);

  Image img(renderer, "resources/img/grass.png");
  SDL_Texture* texture = img.GetTexture();

  uint32_t format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);

  CHECK(img.GetFormat() == format);
}

TEST_CASE("Image::GetAccess", "[Image]") {
  Window window("foo", 10, 10);
  Renderer renderer(window);

  Image img(renderer, "resources/img/grass.png");
  SDL_Texture* texture = img.GetTexture();

  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);

  CHECK(img.GetAccess() == access);
}

TEST_CASE("Image::GetWidth", "[Image]") {
  Window window("foo", 10, 10);
  Renderer renderer(window);

  Image img(renderer, "resources/img/grass.png");
  SDL_Texture* texture = img.GetTexture();

  CHECK(img.GetWidth() == 108);

  int width = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
  CHECK(img.GetWidth() == width);
}

TEST_CASE("Image::GetHeight", "[Image]") {
  Window window("foo", 10, 10);
  Renderer renderer(window);

  Image img(renderer, "resources/img/grass.png");
  SDL_Texture* texture = img.GetTexture();

  CHECK(img.GetHeight() == 108);

  int height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &height);
  CHECK(img.GetHeight() == height);
}
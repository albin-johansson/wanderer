#include "catch.hpp"
#include "image.h"
#include "window.h"
#include "renderer.h"
#include "objects.h"
#include "bad_state_exception.h"

using namespace albinjohansson::wanderer;

TEST_CASE("Image(string)", "[Image]") {
  Window window("foo", 10, 10);
  Renderer renderer(window.GetInternalWindow());

  CHECK_THROWS_AS(Image(nullptr, ""), Objects::NullPointerException);
  CHECK_THROWS_AS(Image(renderer.GetInternalRenderer(), "badpath"), BadStateException);

  Image img(renderer.GetInternalRenderer(), "resources/img/grass.png");

  // The grass.png image is 108x108
  CHECK(img.GetWidth() == 108);
  CHECK(img.GetHeight() == 108);
}
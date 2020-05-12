#include "catch.hpp"
#include "viewport.h"
#include <stdexcept>

using namespace albinjohansson::wanderer;

TEST_CASE("Viewport()", "[Viewport]") {
  Viewport viewport;

  CHECK(viewport.get_bounds().x() == 0);
  CHECK(viewport.get_bounds().y() == 0);
  CHECK(viewport.get_bounds().width() == 10);
  CHECK(viewport.get_bounds().height() == 10);
}

TEST_CASE("Viewport(float, float, float, float)", "[Viewport]") {
  CHECK_THROWS_AS(Viewport({0, 1}, {1, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 0}, {1, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 1}, {0, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 1}, {1, 0}), std::invalid_argument);

  Area vp = {2.4f, 32};
  Area level = {19.5f, 7.8f};

  Viewport viewport(vp, level);

  CHECK(viewport.get_bounds().width() == Approx(vp.width));
  CHECK(viewport.get_bounds().height() == Approx(vp.height));
}

TEST_CASE("Viewport::SetWidth", "[Viewport]") {
  Viewport viewport;

  float width = 1935.8f;
  viewport.set_width(width);

  CHECK(viewport.get_bounds().width() == Approx(width));
}

TEST_CASE("Viewport::SetHeight", "[Viewport]") {
  Viewport viewport;

  float height = 3197.2f;
  viewport.set_height(height);

  CHECK(viewport.get_bounds().height() == Approx(height));
}
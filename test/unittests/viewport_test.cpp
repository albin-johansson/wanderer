#include "catch.hpp"
#include "viewport.h"
#include <stdexcept>

using namespace albinjohansson::wanderer;

TEST_CASE("Viewport()", "[Viewport]") {
  Viewport viewport;

  CHECK(viewport.get_bounds().GetX() == 0);
  CHECK(viewport.get_bounds().GetY() == 0);
  CHECK(viewport.get_bounds().GetWidth() == 10);
  CHECK(viewport.get_bounds().GetHeight() == 10);
}

TEST_CASE("Viewport(float, float, float, float)", "[Viewport]") {
  CHECK_THROWS_AS(Viewport({0, 1}, {1, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 0}, {1, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 1}, {0, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 1}, {1, 0}), std::invalid_argument);

  Area vp = {2.4f, 32};
  Area level = {19.5f, 7.8f};

  Viewport viewport(vp, level);

  CHECK(viewport.get_bounds().GetWidth() == Approx(vp.width));
  CHECK(viewport.get_bounds().GetHeight() == Approx(vp.height));
}

TEST_CASE("Viewport::SetWidth", "[Viewport]") {
  Viewport viewport;

  float width = 1935.8f;
  viewport.set_width(width);

  CHECK(viewport.get_bounds().GetWidth() == Approx(width));
  CHECK_THROWS_AS(viewport.set_width(0), std::invalid_argument);
}

TEST_CASE("Viewport::SetHeight", "[Viewport]") {
  Viewport viewport;

  float height = 3197.2f;
  viewport.set_height(height);

  CHECK(viewport.get_bounds().GetHeight() == Approx(height));
  CHECK_THROWS_AS(viewport.set_height(0), std::invalid_argument);
}

TEST_CASE("Viewport::SetLevelWidth", "[Viewport]") {
  Viewport viewport;
  CHECK_THROWS_AS(viewport.set_level_width(0), std::invalid_argument);
  CHECK_THROWS_AS(viewport.set_level_width(-1), std::invalid_argument);
}

TEST_CASE("Viewport::SetLevelHeight", "[Viewport]") {
  Viewport viewport;
  CHECK_THROWS_AS(viewport.set_level_height(0), std::invalid_argument);
  CHECK_THROWS_AS(viewport.set_level_height(-1), std::invalid_argument);
}
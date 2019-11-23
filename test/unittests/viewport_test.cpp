#include "catch.hpp"
#include "viewport.h"
#include <stdexcept>

using namespace albinjohansson::wanderer;

TEST_CASE("Viewport()", "[Viewport]") {
  Viewport viewport;

  CHECK(viewport.GetBounds().GetX() == 0);
  CHECK(viewport.GetBounds().GetY() == 0);
  CHECK(viewport.GetBounds().GetWidth() == 10);
  CHECK(viewport.GetBounds().GetHeight() == 10);
}

TEST_CASE("Viewport(float, float, float, float)", "[Viewport]") {
  CHECK_THROWS_AS(Viewport({0, 1}, {1, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 0}, {1, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 1}, {0, 1}), std::invalid_argument);
  CHECK_THROWS_AS(Viewport({1, 1}, {1, 0}), std::invalid_argument);

  Area vp = {2.4f, 32};
  Area level = {19.5f, 7.8f};

  Viewport viewport(vp, level);

  CHECK(viewport.GetBounds().GetWidth() == Approx(vp.width));
  CHECK(viewport.GetBounds().GetHeight() == Approx(vp.height));
}

TEST_CASE("Viewport::SetWidth", "[Viewport]") {
  Viewport viewport;

  float width = 1935.8f;
  viewport.SetWidth(width);

  CHECK(viewport.GetBounds().GetWidth() == Approx(width));
  CHECK_THROWS_AS(viewport.SetWidth(0), std::invalid_argument);
}

TEST_CASE("Viewport::SetHeight", "[Viewport]") {
  Viewport viewport;

  float height = 3197.2f;
  viewport.SetHeight(height);

  CHECK(viewport.GetBounds().GetHeight() == Approx(height));
  CHECK_THROWS_AS(viewport.SetHeight(0), std::invalid_argument);
}

TEST_CASE("Viewport::SetLevelWidth", "[Viewport]") {
  Viewport viewport;
  CHECK_THROWS_AS(viewport.SetLevelWidth(0), std::invalid_argument);
  CHECK_THROWS_AS(viewport.SetLevelWidth(-1), std::invalid_argument);
}

TEST_CASE("Viewport::SetLevelHeight", "[Viewport]") {
  Viewport viewport;
  CHECK_THROWS_AS(viewport.SetLevelHeight(0), std::invalid_argument);
  CHECK_THROWS_AS(viewport.SetLevelHeight(-1), std::invalid_argument);
}
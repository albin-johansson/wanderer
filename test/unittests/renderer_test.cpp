#include "catch.hpp"
#include "renderer.h"
#include "require.h"
#include "image.h"
#include <memory>

using namespace centurion;
using namespace albinjohansson::wanderer;

TEST_CASE("RendererCtor1", "[Renderer]") {
  SDL_Renderer* r = nullptr;
  CHECK_THROWS_AS(Renderer(r), Require::NullPointerException);
}

TEST_CASE("RendererCtor2", "[Renderer]") {
  SDL_Window* w = nullptr;
  CHECK_THROWS_AS(Renderer(w), Require::NullPointerException);
}

TEST_CASE("Renderer::RenderTexture2", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  auto img = std::make_unique<Image>(renderer, "resources/img/grass.png");

  CHECK_NOTHROW(renderer.draw_image(*img, 0, 0, 0, 0));
}

TEST_CASE("Renderer::RenderFillRect", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  CHECK_NOTHROW(renderer.fill_rect(0, 0, 0, 0));
}

TEST_CASE("Renderer::SetViewport", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));

  auto viewport = FRectangle(12, 5, {43, 95});
  renderer.set_viewport(viewport);

  auto rendererViewport = renderer.get_viewport();
  CHECK(viewport.GetX() == rendererViewport.GetX());
  CHECK(viewport.GetY() == rendererViewport.GetY());
  CHECK(viewport.GetWidth() == rendererViewport.GetWidth());
  CHECK(viewport.GetHeight() == rendererViewport.GetHeight());
}

TEST_CASE("Renderer::SetScale", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));

  SECTION("Check default scale values.") {
    CHECK(renderer.get_x_scale() == 1);
    CHECK(renderer.get_y_scale() == 1);
  }

  SECTION("Ensure tolerance of bad args.") {
    float beforeXScale = renderer.get_x_scale();
    float beforeYScale = renderer.get_y_scale();
    CHECK_NOTHROW(renderer.set_scale(0, 0));
    CHECK_NOTHROW(renderer.set_scale(-1, -1));

    CHECK(beforeXScale == renderer.get_x_scale());
    CHECK(beforeYScale == renderer.get_y_scale());
  }

  float xScale = 1.5f;
  float yScale = 0.4f;

  renderer.set_scale(xScale, yScale);
  CHECK(renderer.get_x_scale() == xScale);
  CHECK(renderer.get_y_scale() == yScale);
}

TEST_CASE("Renderer::SetLogicalSize", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));

  SECTION("Ensure tolerance of bad args.") {
    float beforeWidth = renderer.get_logical_width();
    float beforeHeight = renderer.get_logical_height();
    CHECK_NOTHROW(renderer.set_logical_size(0, 0));
    CHECK_NOTHROW(renderer.set_logical_size(-1, -1));

    CHECK(beforeWidth == renderer.get_logical_width());
    CHECK(beforeHeight == renderer.get_logical_height());
  }

  float width = 1284;
  float height = 834;
  renderer.set_logical_size(width, height);

  CHECK(width == renderer.get_logical_width());
  CHECK(height == renderer.get_logical_height());
}

TEST_CASE("Renderer::SetLogicalIntegerScale", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));

  CHECK(!renderer.is_using_integer_logical_scaling());

  renderer.set_logical_integer_scale(true);
  CHECK(renderer.is_using_integer_logical_scaling());

  renderer.set_logical_integer_scale(false);
  CHECK(!renderer.is_using_integer_logical_scaling());
}

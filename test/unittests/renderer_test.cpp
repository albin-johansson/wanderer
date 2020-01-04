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

  CHECK_NOTHROW(renderer.RenderTexture(*img, 0, 0, 0, 0));
}

TEST_CASE("Renderer::RenderFillRect", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  CHECK_NOTHROW(renderer.RenderFillRect(0, 0, 0, 0));
}

TEST_CASE("Renderer::SetViewport", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));

  auto viewport = FRectangle(12, 5, {43, 95});
  renderer.SetViewport(viewport);

  auto rendererViewport = renderer.GetViewport();
  CHECK(viewport.GetX() == rendererViewport.GetX());
  CHECK(viewport.GetY() == rendererViewport.GetY());
  CHECK(viewport.GetWidth() == rendererViewport.GetWidth());
  CHECK(viewport.GetHeight() == rendererViewport.GetHeight());
}

TEST_CASE("Renderer::SetScale", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));

  SECTION("Check default scale values.") {
    CHECK(renderer.GetXScale() == 1);
    CHECK(renderer.GetYScale() == 1);
  }

  SECTION("Ensure tolerance of bad args.") {
    float beforeXScale = renderer.GetXScale();
    float beforeYScale = renderer.GetYScale();
    CHECK_NOTHROW(renderer.SetScale(0, 0));
    CHECK_NOTHROW(renderer.SetScale(-1, -1));

    CHECK(beforeXScale == renderer.GetXScale());
    CHECK(beforeYScale == renderer.GetYScale());
  }

  float xScale = 1.5f;
  float yScale = 0.4f;

  renderer.SetScale(xScale, yScale);
  CHECK(renderer.GetXScale() == xScale);
  CHECK(renderer.GetYScale() == yScale);
}

TEST_CASE("Renderer::SetLogicalSize", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));

  SECTION("Ensure tolerance of bad args.") {
    float beforeWidth = renderer.GetLogicalWidth();
    float beforeHeight = renderer.GetLogicalHeight();
    CHECK_NOTHROW(renderer.SetLogicalSize(0, 0));
    CHECK_NOTHROW(renderer.SetLogicalSize(-1, -1));

    CHECK(beforeWidth == renderer.GetLogicalWidth());
    CHECK(beforeHeight == renderer.GetLogicalHeight());
  }

  float width = 1284;
  float height = 834;
  renderer.SetLogicalSize(width, height);

  CHECK(width == renderer.GetLogicalWidth());
  CHECK(height == renderer.GetLogicalHeight());
}

TEST_CASE("Renderer::SetLogicalIntegerScale", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));

  CHECK(!renderer.GetUsingIntegerLogicalScaling());

  renderer.SetLogicalIntegerScale(true);
  CHECK(renderer.GetUsingIntegerLogicalScaling());

  renderer.SetLogicalIntegerScale(false);
  CHECK(!renderer.GetUsingIntegerLogicalScaling());
}

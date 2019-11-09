#include "catch.hpp"
#include "renderer.h"
#include "objects.h"

using namespace wanderer::visuals;
using namespace wanderer::core;

TEST_CASE("RendererCtor1", "[Renderer]") {
  SDL_Renderer* r = nullptr;
  CHECK_THROWS_AS(Renderer(r), Objects::NullPointerException);
}

TEST_CASE("RendererCtor2", "[Renderer]") {
  SDL_Window* w = nullptr;
  CHECK_THROWS_AS(Renderer(w), Objects::NullPointerException);
}

TEST_CASE("Renderer::RenderTexture1", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  CHECK_NOTHROW(renderer.RenderTexture(nullptr, 0, 0));
}

TEST_CASE("Renderer::RenderTexture2", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  CHECK_NOTHROW(renderer.RenderTexture(nullptr, 0, 0, 10, 10));

  SDL_Texture* img = IMG_LoadTexture(renderer.GetInternalRenderer(), "resources/grass.png");
  CHECK_NOTHROW(renderer.RenderTexture(img, 0, 0, 0, 0));
  SDL_DestroyTexture(img);
}

TEST_CASE("Renderer::RenderFillRect", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  CHECK_NOTHROW(renderer.RenderFillRect(0, 0, 0, 0));
}
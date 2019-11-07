#include "catch.hpp"
#include "renderer.h"

using namespace wanderer::view;

TEST_CASE("Ctor1", "[Renderer]") {
  SDL_Renderer* r = nullptr;
  CHECK_THROWS_AS(Renderer(r), std::invalid_argument);
}

TEST_CASE("Ctor2", "[Renderer]") {
  SDL_Window* w = nullptr;
  CHECK_THROWS_AS(Renderer(w), std::invalid_argument);
}

TEST_CASE("RenderTexture1", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  CHECK_NOTHROW(renderer.RenderTexture(nullptr, 0, 0));
}

TEST_CASE("RenderTexture2", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  CHECK_NOTHROW(renderer.RenderTexture(nullptr, 0, 0, 10, 10));

  SDL_Texture* img = IMG_LoadTexture(renderer.GetInternalRenderer(), "resources/grass.png");
  CHECK_NOTHROW(renderer.RenderTexture(img, 0, 0, 0, 0));
  SDL_DestroyTexture(img);
}

TEST_CASE("RenderFillRect", "[Renderer]") {
  Renderer renderer(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN));
  CHECK_NOTHROW(renderer.RenderFillRect(0, 0, 0, 0));
}
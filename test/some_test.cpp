#include "catch.hpp"
#include <SDL.h>
#include <iostream>
#include "some_class.h"

TEST_CASE("SDLTest", "[SDL]") {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Failed to initialize SDL!" << std::endl;
    FAIL();
  } else {
    std::cout << "Success initializing SDL!" << std::endl;
    SDL_Quit();
  }

  REQUIRE(1 == 1);
}

TEST_CASE("DefaultDeps", "[Misc]") {
  wanderer::core::SomeClass sc;
  REQUIRE(sc.AddOne(1) == 2);
}
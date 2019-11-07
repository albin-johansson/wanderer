#include "catch.hpp"
#include "bool_converter.h"

using namespace wanderer::service;

TEST_CASE("Convert", "[BoolConverter]") {
  CHECK(BoolConverter::Convert(true) == SDL_TRUE);
  CHECK(BoolConverter::Convert(false) == SDL_FALSE);
}
#include "catch.hpp"
#include "centurion/bool_converter.h"

using namespace centurion;

TEST_CASE("BoolConverter::Convert", "[BoolConverter]") {
  CHECK(BoolConverter::convert(true) == SDL_TRUE);
  CHECK(BoolConverter::convert(false) == SDL_FALSE);
}
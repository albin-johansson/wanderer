#include "wanderer/misc/fmt_specializations.hpp"

#include <doctest/doctest.h>

TEST_SUITE("fmt::formatter specializations")
{
  TEST_CASE("cen::point")
  {
    const cen::fpoint fp{48.3f, 19.2f};
    const cen::ipoint ip{787, 903};

    CHECK("(48.3, 19.2)" == fmt::format("{}", fp));
    CHECK("(787, 903)" == fmt::format("{}", ip));
  }

  TEST_CASE("cen::area")
  {
    const cen::farea fa{258.6f, 193.2f};
    const cen::iarea ia{1543, 2956};

    CHECK("(258.6, 193.2)" == fmt::format("{}", fa));
    CHECK("(1543, 2956)" == fmt::format("{}", ia));
  }

  TEST_CASE("cen::rect")
  {
    const cen::frect frect{78.9f, 32.8f, 743.3f, 341.1f};
    const cen::irect irect{98, 134, 84, 42};

    CHECK("(78.9, 32.8, 743.3, 341.1)" == fmt::format("{}", frect));
    CHECK("(98, 134, 84, 42)" == fmt::format("{}", irect));
  }

  TEST_CASE("glm::vec2")
  {
    const glm::fvec2 fvec{83.2f, 93.5f};
    const glm::ivec2 ivec{42, -93};

    CHECK("(83.2, 93.5)" == fmt::format("{}", fvec));
    CHECK("(42, -93)" == fmt::format("{}", ivec));
  }

  TEST_CASE("glm::vec3")
  {
    const glm::fvec3 fvec{849.0f, -245.7f, 563.3f};
    const glm::ivec3 ivec{-342, 59, 123};

    CHECK("(849, -245.7, 563.3)" == fmt::format("{}", fvec));
    CHECK("(-342, 59, 123)" == fmt::format("{}", ivec));
  }

  TEST_CASE("glm::vec4")
  {
    const glm::fvec4 fvec{78.5f, 76.8f, 31.1f, 44.4f};
    const glm::ivec4 ivec{9, 51, 3821, 832};

    CHECK("(78.5, 76.8, 31.1, 44.4)" == fmt::format("{}", fvec));
    CHECK("(9, 51, 3821, 832)" == fmt::format("{}", ivec));
  }
}

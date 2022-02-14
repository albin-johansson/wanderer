#include "wanderer/core/centurion_utils.hpp"

#include <doctest/doctest.h>

using namespace wanderer;

TEST_SUITE("Centurion utilities")
{
  TEST_CASE("as_point[glm::vec2]")
  {
    const glm::vec2 vec{42.5f, 95.2f};
    const auto point = as_point(vec);
    CHECK(vec.x == point.x());
    CHECK(vec.y == point.y());
  }

  TEST_CASE("as_point[glm::ivec2]")
  {
    const glm::ivec2 vec{832, -392};
    const auto point = as_point(vec);
    CHECK(vec.x == point.x());
    CHECK(vec.y == point.y());
  }

  TEST_CASE("as_rect[glm::vec4]")
  {
    const glm::vec4 vec{54, 393, 422, 284};
    const auto rect = as_rect(vec);
    CHECK(vec.x == rect.x());
    CHECK(vec.y == rect.y());
    CHECK(vec.z == rect.width());
    CHECK(vec.w == rect.height());
  }

  TEST_CASE("as_rect[glm::ivec4]")
  {
    const glm::ivec4 vec{-82, 730, 41, 9384};
    const auto rect = as_rect(vec);
    CHECK(vec.x == rect.x());
    CHECK(vec.y == rect.y());
    CHECK(vec.z == rect.width());
    CHECK(vec.w == rect.height());
  }

  TEST_CASE("as_rect[glm::vec2, glm::vec2]")
  {
    const glm::vec2 pos{6374, 769};
    const glm::vec2 size{387, 92};
    const auto rect = as_rect(pos, size);
    CHECK(pos.x == rect.x());
    CHECK(pos.y == rect.y());
    CHECK(size.x == rect.width());
    CHECK(size.y == rect.height());
  }

  TEST_CASE("as_rect[glm::ivec2, glm::ivec2]")
  {
    const glm::ivec2 pos{7, -132};
    const glm::ivec2 size{724, 8473};
    const auto rect = as_rect(pos, size);
    CHECK(pos.x == rect.x());
    CHECK(pos.y == rect.y());
    CHECK(size.x == rect.width());
    CHECK(size.y == rect.height());
  }
}

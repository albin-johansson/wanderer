#include "parse_light.hpp"

#include <cassert>  // assert

namespace wanderer::io {

auto parse_light(const rune::tmx_object& object, const float xRatio, const float yRatio)
    -> comp::point_light
{
  assert(object.is_ellipse);

  comp::point_light light;
  light.size = object.width * xRatio;

  const auto x = object.x * xRatio;
  const auto y = object.y * yRatio;

  light.position.x = x + (light.size / 2.0f);
  light.position.y = y + (light.size / 2.0f);

  light.fluctuation_limit = 5;
  light.fluctuation_step = 1;
  light.fluctuation = 0;

  if (const auto* limit = rune::tmx::try_get_float(object.properties, "fluctuationLimit"))
  {
    light.fluctuation_limit = *limit;
  }

  if (const auto* step = rune::tmx::try_get_float(object.properties, "fluctuationStep"))
  {
    light.fluctuation_step = *step;
  }

  return light;
}

}  // namespace wanderer::io

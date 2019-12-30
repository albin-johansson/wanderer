#pragma once
#include <variant>

namespace albinjohansson::wanderer {

/**
 * A simple struct that describes an area, that uses floating-point values.
 *
 * @since 0.1.0
 */
struct Area {
  float width = 0;
  float height = 0;
};

}

#pragma once

#include <string_view>  // string_view

#include "wanderer_std.hpp"

namespace wanderer {

enum class DayOfWeek
{
  Monday = 0,
  Tuesday = 1,
  Wednesday = 2,
  Thursday = 3,
  Friday = 4,
  Saturday = 5,
  Sunday = 6
};

[[nodiscard]] auto Stringify(DayOfWeek day) -> std::string_view;

[[nodiscard]] auto ParseDayOfWeek(std::string_view str) -> Maybe<DayOfWeek>;

}  // namespace wanderer

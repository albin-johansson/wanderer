#include "day.hpp"

#include <magic_enum.hpp>

#include "wanderer/misc/exception.hpp"

namespace wanderer {

auto full_name(const DayOfWeek day) -> std::string_view
{
  return magic_enum::enum_name(day);
}

auto short_name(const DayOfWeek day) -> std::string_view
{
  switch (day) {
    case DayOfWeek::monday:
      return "MON";

    case DayOfWeek::tuesday:
      return "TUE";

    case DayOfWeek::wednesday:
      return "WED";

    case DayOfWeek::thursday:
      return "THU";

    case DayOfWeek::friday:
      return "FRI";

    case DayOfWeek::saturday:
      return "SAT";

    case DayOfWeek::sunday:
      return "SUN";

    default:
      throw_traced(WandererError{"Invalid day!"});
  }
}

}  // namespace wanderer
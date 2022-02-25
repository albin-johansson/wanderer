#include "day.hpp"

#include <magic_enum.hpp>

#include "wanderer/misc/exception.hpp"

namespace wanderer {

auto full_name(const day_of_week day) -> std::string_view
{
  return magic_enum::enum_name(day);
}

auto short_name(const day_of_week day) -> std::string_view
{
  switch (day) {
    case day_of_week::monday:
      return "MON";

    case day_of_week::tuesday:
      return "TUE";

    case day_of_week::wednesday:
      return "WED";

    case day_of_week::thursday:
      return "THU";

    case day_of_week::friday:
      return "FRI";

    case day_of_week::saturday:
      return "SAT";

    case day_of_week::sunday:
      return "SUN";

    default:
      throw_traced(wanderer_error{"Invalid day!"});
  }
}

}  // namespace wanderer
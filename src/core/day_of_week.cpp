#include "day_of_week.hpp"

namespace wanderer {

auto Stringify(const DayOfWeek day) -> std::string_view
{
  switch (day) {
    case DayOfWeek::Monday:
      return "MON";

    case DayOfWeek::Tuesday:
      return "TUE";

    case DayOfWeek::Wednesday:
      return "WED";

    case DayOfWeek::Thursday:
      return "THU";

    case DayOfWeek::Friday:
      return "FRI";

    case DayOfWeek::Saturday:
      return "SAT";

    case DayOfWeek::Sunday:
      return "SUN";

    default:
      throw WandererError{"Did not recognize day of week!"};
  }
}

auto ParseDayOfWeek(const std::string_view str) -> Maybe<DayOfWeek>
{
  if (str == "MON" || str == "mon") {
    return DayOfWeek::Monday;
  }
  else if (str == "TUE" || str == "tue") {
    return DayOfWeek::Tuesday;
  }
  else if (str == "WED" || str == "wed") {
    return DayOfWeek::Wednesday;
  }
  else if (str == "THU" || str == "thu") {
    return DayOfWeek::Thursday;
  }
  else if (str == "FRI" || str == "fri") {
    return DayOfWeek::Friday;
  }
  else if (str == "SAT" || str == "sat") {
    return DayOfWeek::Saturday;
  }
  else if (str == "SUN" || str == "sun") {
    return DayOfWeek::Sunday;
  }
  else {
    return std::nullopt;
  }
}

}  // namespace wanderer
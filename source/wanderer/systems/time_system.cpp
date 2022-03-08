#include "time_system.hpp"

#include <cmath>   // floor, ceil
#include <vector>  // vector

#include "wanderer/data/components/world.hpp"
#include "wanderer/misc/logging.hpp"

namespace wanderer::sys {
namespace {

constexpr float32 _time_rate = 5'000;

constexpr float32 _sunrise_hour = 6;
constexpr float32 _daytime_hour = 9;
constexpr float32 _sunset_hour = 18;
constexpr float32 _night_hour = 21;

struct day_phase final
{
  float32 start_hour{};
  float32 end_hour{};
  std::vector<cen::color> colors;
};

constexpr auto _black = cen::colors::black;
constexpr auto _orange = cen::colors::orange;
constexpr auto _navy = cen::colors::navy;

const auto _sunrise_color = cen::blend(_black, _orange, 0.5f).with_alpha(0x20);
const auto _sunrise_end_color = cen::blend(_black, _orange, 0.25f).with_alpha(0x20);

const auto _day_color = _black.with_alpha(0);
const auto _day_end_color = cen::blend(_black, _orange, 0.25f).with_alpha(0x20);

const auto _sunset_color = cen::blend(_black, _orange, 0.5f).with_alpha(0x20);
const auto _night_color = cen::blend(_black, _navy, 0.3f).with_alpha(0xDD);

const day_phase _sunrise_phase{_sunrise_hour,
                               _daytime_hour,
                               {_night_color, _sunrise_color, _sunrise_end_color}};

const day_phase _day_phase{_daytime_hour,
                           _sunset_hour,
                           {_sunrise_end_color, _day_color, _day_end_color}};

const day_phase _sunset_phase{_sunset_hour,
                              _night_hour,
                              {_day_end_color, _sunset_color, _night_color}};

/* Night phase can only have one color */
const day_phase _night_phase{_night_hour, _sunrise_hour, {_night_color}};

[[nodiscard]] auto _get_tint(const day_phase& current, const float32 hour) -> cen::color
{
  if (current.colors.size() == 1) {
    return current.colors.at(0);
  }
  else {
    const auto now = hour - current.start_hour;
    const auto duration = current.end_hour - current.start_hour;
    const auto progression = now / duration;

    const auto lastIndex = static_cast<float32>(cen::isize(current.colors)) - 1.0f;
    const auto index = progression * lastIndex;
    const auto indexLower = std::floor(index);
    const auto indexUpper = std::ceil(index);

    const auto c1 = current.colors.at(static_cast<usize>(indexLower));
    const auto c2 = current.colors.at(static_cast<usize>(indexUpper));

    return cen::blend(c1, c2, index - indexLower);
  }
}

[[nodiscard]] auto _get_phase(const float32 hour) -> const day_phase&
{
  if (hour > _sunrise_hour && hour <= _daytime_hour) {
    return _sunrise_phase;
  }
  else if (hour > _daytime_hour && hour <= _sunset_hour) {
    return _day_phase;
  }
  else if (hour > _sunset_hour && hour <= _night_hour) {
    return _sunset_phase;
  }
  else {
    return _night_phase;
  }
}

[[nodiscard]] constexpr auto _day_after(const day_of_week day) noexcept -> day_of_week
{
  return day_of_week{(cen::to_underlying(day) + 1) % 7};
}

}  // namespace

void update_time(entt::registry& registry, entt::dispatcher& dispatcher, const float32 dt)
{
  auto& date = registry.ctx<comp::DateAndTime>();

  date.seconds += _time_rate * dt;
  date.minute = date.seconds / 60.0f;
  date.hour = date.minute / 60.0f;

  const auto& phase = _get_phase(date.hour);
  date.tint = _get_tint(phase, date.hour);

  if (date.hour >= 24) {
    date.day = _day_after(date.day);
    date.hour = 0;
    date.minute = 0;
    date.seconds = 0;

    debug("Changing day to '{}'", full_name(date.day));

    // TODO emit event
  }
}

}  // namespace wanderer::sys
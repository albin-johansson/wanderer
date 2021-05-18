#include "time_system.hpp"

#include <centurion.hpp>  // to_underlying, ...
#include <cmath>          // floor, ceil, lerp
#include <rune.hpp>       // static_vector
#include <stdexcept>      // runtime_error
#include <string>         // string
#include <string_view>    // string_view

#include "components/ctx/time_of_day.hpp"
#include "core/common_concepts.hpp"
#include "events/day_changed_event.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float rate = 100;

inline constexpr float sunrise = 6;
inline constexpr float daytime = 8.5f;
inline constexpr float sunset = 18;
inline constexpr float night = 22;

struct phase final
{
  float phase_start;
  float phase_end;
  rune::static_vector<cen::color, 5> colors;
};

inline const phase sunrise_phase{
    .phase_start = sunrise,
    .phase_end = daytime,
    .colors = {cen::blend(cen::colors::black, cen::colors::navy, 0.3),
               cen::colors::orange}};

inline const phase day_phase{
    .phase_start = daytime,
    .phase_end = sunset,
    .colors = {cen::colors::orange,
               cen::blend(cen::colors::white, cen::colors::orange),
               cen::colors::white,
               cen::blend(cen::colors::white, cen::colors::orange, 0.2),
               cen::blend(cen::colors::white, cen::colors::orange, 0.4)}};

inline const phase sunset_phase{
    .phase_start = sunset,
    .phase_end = night,
    .colors = {cen::blend(cen::colors::white, cen::colors::orange, 0.4),
               cen::blend(cen::colors::white, cen::colors::orange, 0.75),
               cen::colors::orange,
               cen::blend(cen::colors::black, cen::colors::navy, 0.6),
               cen::blend(cen::colors::black, cen::colors::navy, 0.3)}};

inline const phase night_phase{
    .phase_start = night,
    .phase_end = sunrise,
    .colors = {cen::blend(cen::colors::black, cen::colors::navy, 0.3)}};

template <typename T, typename Container, typename Callable>
[[nodiscard]] auto next_value(const phase& current,
                              const Container& container,
                              const float hour,
                              Callable callable) -> T
{
  if (container.size() == 1)
  {
    return container.at(0);
  }
  else
  {
    const auto a = hour - current.phase_start;
    const auto b = current.phase_end - current.phase_start;

    const auto xx = (a / b) * (static_cast<float>(cen::isize(container)) - 1.0f);
    const auto xFloor = std::floor(xx);

    const auto x1 = container.at(static_cast<std::size_t>(xFloor));
    const auto x2 = container.at(static_cast<std::size_t>(std::ceil(xx)));

    return callable(x1, x2, xx - xFloor);
  }
}

[[nodiscard]] auto get_color(const phase& current, const float hour) -> cen::color
{
  return next_value<cen::color>(current, current.colors, hour, cen::blend);
}

[[nodiscard]] auto get_phase(const float hour) -> const phase&
{
  if (hour > sunrise && hour <= daytime)
  {
    return sunrise_phase;
  }
  else if (hour > daytime && hour <= sunset)
  {
    return day_phase;
  }
  else if (hour > sunset && hour <= night)
  {
    return sunset_phase;
  }
  else
  {
    return night_phase;
  }
}

[[nodiscard]] constexpr auto next_day(const day_of_week day) noexcept -> day_of_week
{
  return static_cast<day_of_week>((cen::to_underlying(day) + 1) % 7);
}

[[nodiscard]] constexpr auto to_string(const day_of_week day) -> std::string_view
{
  switch (day)
  {
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
      throw std::runtime_error{"Did not recognize day of week!"};
  }
}

}  // namespace

void update_time(entt::registry& shared,
                 entt::dispatcher& dispatcher,
                 const rune::delta_time dt)
{
  auto& time = shared.ctx<ctx::time_of_day>();

  time.seconds += rate * dt;
  time.minute = time.seconds / 60.0f;
  time.hour = time.minute / 60.0f;

  const auto& phase = get_phase(time.hour);
  time.tint = get_color(phase, time.hour);

  if (time.hour >= 24)
  {
    time.seconds = 0;
    time.day = next_day(time.day);

    /* Note, string_view::data is not guaranteed to be null-terminated, but
       we know it is here. */
    CENTURION_LOG_INFO("Changed day to %s", to_string(time.day).data());

    dispatcher.enqueue<day_changed_event>(time.day);
  }
}

void render_clock(const entt::registry& registry, graphics_context& graphics)
{
  const auto& time = registry.ctx<const ctx::time_of_day>();

  const auto hour = static_cast<int>(time.hour) % 24;
  const auto minute = static_cast<int>(time.minute) % 60;

  const auto prefix = [](const int value) {
    return (value < 10) ? std::string{"0"} : std::string{};
  };

  graphics.render_outlined_text(to_string(time.day), cen::point(6, 6));
  graphics.render_outlined_text(prefix(hour) + std::to_string(hour) + ": " +
                                    prefix(minute) + std::to_string(minute),
                                cen::point(30, 6));
}

}  // namespace wanderer::sys

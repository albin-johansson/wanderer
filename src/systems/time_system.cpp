#include "time_system.hpp"

#include <array>        // array
#include <cmath>        // floor, ceil, lerp
#include <stdexcept>    // runtime_error
#include <string_view>  // string_view

#include <centurion.hpp>        // to_underlying, ...
#include <rune/everything.hpp>  // static_vector, formatted_string

#include "components/ctx/time_of_day.hpp"
#include "core/common_concepts.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/day_changed_event.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float seconds_per_hour = 3'600;
inline constexpr float rate = 100;

inline constexpr float sunrise = glob::morning_hour;
inline constexpr float daytime = 8;
inline constexpr float sunset = 20;
inline constexpr float night = 22;

struct phase final
{
  float phase_start{};
  float phase_end{};
  rune::static_vector<cen::color, 5> colors;
};

inline constexpr auto black = cen::colors::black;
inline constexpr auto orange = cen::colors::orange;
inline constexpr auto navy = cen::colors::navy;

inline const auto sunrise_color = cen::blend(black, orange, 0.5f).with_alpha(0x20);
inline const auto sunrise_end_color = cen::blend(black, orange, 0.25f).with_alpha(0x20);

inline const auto day_color = black.with_alpha(0);
inline const auto day_end_color = cen::blend(black, orange, 0.25f).with_alpha(0x20);

inline const auto sunset_color = cen::blend(black, orange, 0.5f).with_alpha(0x20);
inline const auto night_color = cen::blend(black, navy, 0.3f).with_alpha(0xDD);

inline const phase sunrise_phase{
    .phase_start = sunrise,
    .phase_end = daytime,
    .colors = {night_color, sunrise_color, sunrise_end_color}};

inline const phase day_phase{.phase_start = daytime,
                             .phase_end = sunset,
                             .colors = {sunrise_end_color, day_color, day_end_color}};

inline const phase sunset_phase{.phase_start = sunset,
                                .phase_end = night,
                                .colors = {day_end_color, sunset_color, night_color}};

// Night phase can only have one color
inline const phase night_phase{.phase_start = night,
                               .phase_end = sunrise,
                               .colors = {night_color}};

[[nodiscard]] auto get_color(const phase& current, const float hour) -> cen::color
{
  if (current.colors.size() == 1) {
    return current.colors.at(0);
  }
  else {
    const auto now = hour - current.phase_start;
    const auto duration = current.phase_end - current.phase_start;
    const auto progression = now / duration;

    const auto lastIndex = static_cast<float>(cen::isize(current.colors)) - 1.0f;
    const auto index = progression * lastIndex;
    const auto indexLower = std::floor(index);
    const auto indexUpper = std::ceil(index);

    const auto c1 = current.colors.at(static_cast<usize>(indexLower));
    const auto c2 = current.colors.at(static_cast<usize>(indexUpper));

    return cen::blend(c1, c2, index - indexLower);
  }
}

[[nodiscard]] auto get_phase(const float hour) -> const phase&
{
  if (hour > sunrise && hour <= daytime) {
    return sunrise_phase;
  }
  else if (hour > daytime && hour <= sunset) {
    return day_phase;
  }
  else if (hour > sunset && hour <= night) {
    return sunset_phase;
  }
  else {
    return night_phase;
  }
}

[[nodiscard]] constexpr auto next_day(const DayOfWeek day) noexcept -> DayOfWeek
{
  return static_cast<DayOfWeek>((cen::to_underlying(day) + 1) % 7);
}

[[nodiscard]] constexpr auto to_string(const DayOfWeek day) -> std::string_view
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
      throw std::runtime_error{"Did not recognize day of week!"};
  }
}

}  // namespace

void UpdateTime(entt::registry& shared, entt::dispatcher& dispatcher, float dt)
{
  auto& time = shared.ctx<ctx::TimeOfDay>();

  time.seconds += rate * dt;
  time.minute = time.seconds / 60.0f;
  time.hour = time.minute / 60.0f;

  const auto& phase = get_phase(time.hour);
  time.tint = get_color(phase, time.hour);

  if (time.hour >= 24) {
    ChangeToNextDay(shared, dispatcher);
  }
}

void ChangeToNextDay(entt::registry& shared, entt::dispatcher& dispatcher, float hour)
{
  auto& time = shared.ctx<ctx::TimeOfDay>();
  time.seconds = hour * seconds_per_hour;
  time.day = next_day(time.day);

  /* Note, string_view::data is not guaranteed to be null-terminated, but
     we know it is here. */
  CENTURION_LOG_INFO("Changed day to %s", to_string(time.day).data());

  dispatcher.enqueue<DayChangedEvent>(time.day);
}

void RenderClock(const entt::registry& registry)
{
  const auto& time = registry.ctx<ctx::TimeOfDay>();

  const auto hour = static_cast<int>(time.hour) % 24;
  const auto minute = static_cast<int>(time.minute) % 60;

  const auto prefix = [](const int value) -> std::string_view {
    return (value < 10) ? "0" : "";
  };

  const rune::formatted_string<64> str{"{}{}: {}{}",
                                       prefix(hour),
                                       hour,
                                       prefix(minute),
                                       minute};

  auto& graphics = registry.ctx<ref<GraphicsContext>>().get();
  graphics.render_outlined_text(to_string(time.day), cen::point(6, 6));
  graphics.render_outlined_text(str.view(), cen::point(30, 6));
}

}  // namespace wanderer::sys

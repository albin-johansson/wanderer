#include "time_system.hpp"

#include <cmath>  // floor, ceil, lerp

#include "components/ctx/time_of_day.hpp"
#include "core/common_concepts.hpp"
#include "core/static_vector.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float rate = 100;

inline constexpr float sunrise = 6;
inline constexpr float daytime = 8.5f;
inline constexpr float sunset = 18;
inline constexpr float night = 22;

struct phase final
{
  float phaseStart;
  float phaseEnd;
  static_vector<cen::color, 5> colors;
};

inline const phase sunrise_phase{
    .phaseStart = sunrise,
    .phaseEnd = daytime,
    .colors = {cen::color::blend(cen::colors::black, cen::colors::navy, 0.3),
               cen::colors::orange}};

inline const phase day_phase{
    .phaseStart = daytime,
    .phaseEnd = sunset,
    .colors = {cen::colors::orange,
               cen::color::blend(cen::colors::white, cen::colors::orange),
               cen::colors::white,
               cen::color::blend(cen::colors::white, cen::colors::orange, 0.2),
               cen::color::blend(cen::colors::white, cen::colors::orange, 0.4)}};

inline const phase sunset_phase{
    .phaseStart = sunset,
    .phaseEnd = night,
    .colors = {cen::color::blend(cen::colors::white, cen::colors::orange, 0.4),
               cen::color::blend(cen::colors::white, cen::colors::orange, 0.75),
               cen::colors::orange,
               cen::color::blend(cen::colors::black, cen::colors::navy, 0.6),
               cen::color::blend(cen::colors::black, cen::colors::navy, 0.3)}};

inline const phase night_phase{
    .phaseStart = night,
    .phaseEnd = sunrise,
    .colors = {cen::color::blend(cen::colors::black, cen::colors::navy, 0.3)}};

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
    const auto a = hour - current.phaseStart;
    const auto b = current.phaseEnd - current.phaseStart;

    const auto xx = (a / b) * (static_cast<float>(cen::isize(container)) - 1.0f);
    const auto xFloor = std::floor(xx);

    const auto x1 = container.at(static_cast<std::size_t>(xFloor));
    const auto x2 = container.at(static_cast<std::size_t>(std::ceil(xx)));

    return callable(x1, x2, xx - xFloor);
  }
}

[[nodiscard]] auto get_color(const phase& current, const float hour) -> cen::color
{
  if (current.colors.size() == 1)
  {
    return current.colors.at(0);
  }
  else
  {
    const auto a = hour - current.phaseStart;
    const auto b = current.phaseEnd - current.phaseStart;

    const auto dd = (a / b) * (static_cast<float>(cen::isize(current.colors)) - 1.0f);
    const auto ddFloor = std::floor(dd);

    const auto c1 = current.colors.at(static_cast<std::size_t>(ddFloor));
    const auto c2 = current.colors.at(static_cast<std::size_t>(std::ceil(dd)));

    return cen::color::blend(c1, c2, dd - ddFloor);
  }
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

}  // namespace

void update_time(entt::registry& registry, const delta_time dt)
{
  auto& time = registry.ctx<ctx::time_of_day>();

  time.seconds += rate * dt;
  time.minute = time.seconds / 60.0f;
  time.hour = time.minute / 60.0f;

  const auto& phase = get_phase(time.hour);
  time.color = get_color(phase, time.hour);

  if (time.hour >= 24)
  {
    // TODO emit day changed event

    time.seconds = 0;
  }
}

void render_clock(const entt::registry& registry, graphics_context& graphics)
{
  auto& renderer = graphics.renderer();
  const auto& time = registry.ctx<const ctx::time_of_day>();

  const auto h = static_cast<int>(time.hour) % 24;
  const auto m = static_cast<int>(time.minute) % 60;

  const auto hourPrefix = (h < 10) ? std::string{"0"} : std::string{};
  const auto minutesPrefix = (m < 10) ? std::string{"0"} : std::string{};

  renderer.render_text(
      graphics.small_font_cache(),
      hourPrefix + std::to_string(h) + ": " + minutesPrefix + std::to_string(m),
      {6, 6});
}

}  // namespace wanderer::sys

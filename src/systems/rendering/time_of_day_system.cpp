#include "time_of_day_system.hpp"

#include <cmath>  // floor, ceil

#include "centurion_utils.hpp"
#include "get_random.hpp"
#include "ints.hpp"
#include "menu_constants.hpp"
#include "time_of_day.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float rate = 100.0f;
inline constexpr float max_darkness = 0.5f;

inline constexpr float sunrise = 6;
inline constexpr float daytime = 8.5f;
inline constexpr float sunset = 18;
inline constexpr float night = 22;

struct phase final
{
  float phaseStart;
  float phaseEnd;
  std::vector<float> opacities;
  std::vector<cen::color> colors;
};

inline const phase sunrise_phase{
    sunrise,
    daytime,
    {max_darkness, 0.2f},
    {merge(cen::colors::black, cen::colors::navy, 0.3), cen::colors::orange}};

inline const phase day_phase{daytime,
                             sunset,
                             {0.2f, 0.0f, 0.0f, 0.0f, 0.2f},
                             {cen::colors::orange,
                              merge(cen::colors::white, cen::colors::orange, 0.5),
                              cen::colors::white,
                              merge(cen::colors::white, cen::colors::orange, 0.5),
                              cen::colors::orange}};

inline const phase sunset_phase{sunset,
                                night,
                                {0.2f, 0.35f},
                                {cen::colors::orange,
                                 merge(cen::colors::black, cen::colors::navy, 0.6),
                                 merge(cen::colors::black, cen::colors::navy, 0.3)}};

inline const phase night_phase{night,
                               sunrise,
                               {max_darkness},
                               {merge(cen::colors::black, cen::colors::navy, 0.3)}};

[[nodiscard]] auto get_color(const phase& currentPhase, const float hour) -> cen::color
{
  if (currentPhase.colors.size() == 1)
  {
    return currentPhase.colors.at(0);
  }
  else
  {
    const auto a = static_cast<double>(hour - currentPhase.phaseStart);
    const auto b = static_cast<double>(currentPhase.phaseEnd - currentPhase.phaseStart);

    const auto cc =
        (a / b) * (static_cast<double>(cen::isize(currentPhase.colors)) - 1.0);
    const auto c1 = currentPhase.colors.at(static_cast<std::size_t>(std::floor(cc)));
    const auto c2 = currentPhase.colors.at(static_cast<std::size_t>(std::ceil(cc)));

    return merge(c1, c2, cc - std::floor(cc));
  }
}

[[nodiscard]] auto get_darkness(const phase& current, const float hour) -> float
{
  if (current.opacities.size() == 1)
  {
    return current.opacities.at(0);
  }
  else
  {
    const auto a = static_cast<double>(hour - current.phaseStart);
    const auto b = static_cast<double>(current.phaseEnd - current.phaseStart);

    const auto dd = (a / b) * (static_cast<double>(cen::isize(current.opacities)) - 1.0);
    const auto d1 = current.opacities.at(static_cast<std::size_t>(std::floor(dd)));
    const auto d2 = current.opacities.at(static_cast<std::size_t>(std::ceil(dd)));

    const auto mergeNumber = [](const float a, const float b, const float bias) {
      return (a * (1.0f - bias)) + (b * bias);
    };

    return mergeNumber(d1, d2, dd - std::floor(dd));
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

void update_time_of_day(entt::registry& registry, const delta_t dt)
{
  auto& time = registry.ctx<ctx::time_of_day>();

  time.seconds += rate * dt;
  time.minute = time.seconds / 60.0f;
  time.hour = time.minute / 60.0f;

  const auto& phase = get_phase(time.hour);
  time.color = get_color(phase, time.hour);
  time.opacity = static_cast<u8>(get_darkness(phase, time.hour) * 255.0);

  if (time.hour >= 24)
  {
    // TODO emit day changed event

    time.seconds = 0;
  }
}

// void render_time_of_day_overlay(const entt::registry& registry,
//                                graphics_context& graphics)
//{
//  const auto& time = registry.ctx<ctx::time_of_day>();
//  auto& renderer = graphics.renderer();
//
//  using namespace entt::literals;
//  const auto index =
//      graphics.load("point-light"_hs, "resources/images/Ardentryst/glow.png");
//
//  cen::texture texture{renderer,
//                       graphics.pixel_format(),
//                       cen::texture_access::target,
//                       glob::logical_size<>};
//  texture.set_alpha(time.opacity);
//
//  const auto translation = renderer.translation_viewport();
//  renderer.set_translation_viewport({});
//  renderer.set_target(&texture);
//
//  texture.set_blend_mode(cen::blend_mode::blend);
//  //  renderer.set_color(time.color.with_alpha(time.opacity));
//  renderer.set_color(time.color);
//  renderer.fill();
//
//  const auto x = (glob::logical_width<> / 2) - 160;
//  const auto y = (glob::logical_height<> / 2) - 160;
//  texture.set_blend_mode(cen::blend_mode::mod);
//
//  static float size = 320;
//  size += get_random(0, 50) < 25 ? -0.5f : 0.5f;
//  size = std::clamp(size, 315.0f, 325.0f);
//
//  graphics.render(index, {{}, {80, 80}}, {{x, y}, {size, size}});
//
//  renderer.set_target(nullptr);
//  renderer.set_translation_viewport(translation);
//
//  renderer.set_blend_mode(cen::blend_mode::blend);
//  renderer.render<int>(texture, {0, 0});
//}

void render_clock(const entt::registry& registry, graphics_context& graphics)
{
  auto& renderer = graphics.renderer();
  const auto& time = registry.ctx<ctx::time_of_day>();

  const auto h = static_cast<int>(time.hour) % 24;
  const auto m = static_cast<int>(time.minute) % 60;

  const auto hourPrefix = h < 10 ? std::string{"0"} : std::string{};
  const auto minutesPrefix = m < 10 ? std::string{"0"} : std::string{};

  const auto hourStr = hourPrefix + std::to_string(h);
  const auto minuteStr = minutesPrefix + std::to_string(m);

  auto& cache = graphics.small_font_cache();
  renderer.render_text(cache, hourStr + ": " + minuteStr, {6, 6});
}

}  // namespace wanderer::sys

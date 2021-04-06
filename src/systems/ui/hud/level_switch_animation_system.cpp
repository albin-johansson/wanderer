#include "level_switch_animation_system.hpp"

#include "game_constants.hpp"
#include "level_switch_animation.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float speed = 150;
inline constexpr float n_steps = 120;
inline constexpr cen::color gray{0x11, 0x11, 0x11};

}  // namespace

void update_level_switch_animations(entt::registry& registry,
                                    entt::dispatcher& dispatcher,
                                    const delta_t dt)
{
  const auto view = registry.view<comp::level_switch_animation>();
  view.each([&](comp::level_switch_animation& animation) {
    animation.width += animation.xStepSize * animation.speed * dt;
    animation.height += animation.yStepSize * animation.speed * dt;

    if (animation.fadingIn)
    {
      if (animation.width >= glob::logical_width<float> / 2.0f)
      {
        dispatcher.enqueue<event::level_faded_in>(animation.map.value(),
                                                  animation.width,
                                                  animation.height,
                                                  -animation.xStepSize,
                                                  -animation.yStepSize);
      }
    }
    else
    {
      if (animation.width <= 0)
      {
        dispatcher.enqueue<event::level_faded_out>();
      }
    }
  });
}

void render_level_switch_animations(const entt::registry& registry,
                                    cen::renderer& renderer)
{
  const auto view = registry.view<const comp::level_switch_animation>();
  view.each([&](const comp::level_switch_animation& animation) noexcept {
    constexpr auto logicalSize = glob::logical_size<cen::farea>;
    constexpr auto width = logicalSize.width;
    constexpr auto height = logicalSize.height;

    const auto hSize = animation.width;
    const auto vSize = animation.height;
    renderer.set_color(gray);
    renderer.fill_rect<float>({{}, {width, vSize}});
    renderer.fill_rect<float>({{0, height - vSize}, {width, vSize}});
    renderer.fill_rect<float>({{}, {hSize, height}});
    renderer.fill_rect<float>({{width - hSize, 0}, {hSize, height}});
  });
}

void start_level_fade_animation(entt::registry& registry, const map_id map)
{
  auto& animation = registry.emplace<comp::level_switch_animation>(registry.create());
  animation.map = map;
  animation.speed = speed;
  animation.width = 0;
  animation.height = 0;
  animation.xStepSize = glob::logical_width<float> / n_steps;
  animation.yStepSize = glob::logical_height<float> / n_steps;
  animation.fadingIn = true;
}

void end_level_fade_animation(entt::registry& registry,
                              const event::level_faded_in& event)
{
  auto& animation = registry.emplace<comp::level_switch_animation>(registry.create());
  animation.map = std::nullopt;
  animation.speed = speed;
  animation.width = event.width;
  animation.height = event.height;
  animation.xStepSize = event.xStepSize;
  animation.yStepSize = event.yStepSize;
  animation.fadingIn = false;
}

}  // namespace wanderer::sys

#include "level_switch_animation_system.hpp"

#include <cen/screen.hpp>

#include "game_constants.hpp"
#include "level_switch_animation.hpp"

namespace wanderer::sys::hud {

void update_level_switch_animations(entt::registry& registry,
                                    entt::dispatcher& dispatcher)
{
  const auto view = registry.view<comp::level_switch_animation>();
  view.each([&](comp::level_switch_animation& animation) {
    if (animation.fadingIn) {
      ++animation.step;
      if (animation.step == animation.nSteps - 1) {
        dispatcher.enqueue<comp::level_faded_in_event>(animation.map.value(),
                                                       animation.step,
                                                       animation.nSteps,
                                                       animation.hStepSize,
                                                       animation.vStepSize);
      }
    } else {
      --animation.step;
      if (animation.step == 0) {
        dispatcher.enqueue<comp::level_faded_out_event>();
      }
    }
  });
}

void render_level_switch_animations(const entt::registry& registry,
                                    cen::renderer& renderer)
{
  const auto view = registry.view<const comp::level_switch_animation>();
  view.each([&](const comp::level_switch_animation& animation) noexcept {
    const auto logicalSize = renderer.logical_size();
    const auto width = static_cast<float>(logicalSize.width);
    const auto height = static_cast<float>(logicalSize.height);

    const auto step = static_cast<float>(animation.step);
    const auto hSize = animation.hStepSize + (step * animation.hStepSize);
    const auto vSize = animation.vStepSize + (step * animation.vStepSize);

    constexpr cen::color gray{0x11, 0x11, 0x11, 0xFF};
    renderer.set_color(gray);

    renderer.fill_rect<float>({{}, {width, vSize}});
    renderer.fill_rect<float>({{0, height - vSize}, {width, vSize}});
    renderer.fill_rect<float>({{}, {hSize, height}});
    renderer.fill_rect<float>({{width - hSize, 0}, {hSize, height}});
  });
}

void start_level_fade_animation(entt::registry& registry, const map_id map)
{
  const auto entity = registry.create();

  auto& anim = registry.emplace<comp::level_switch_animation>(entity);
  anim.map = map;
  anim.step = 0;
  anim.nSteps = static_cast<int>(0.5 * cen::screen::refresh_rate());

  anim.hStepSize =
      (g_logicalWidth<float> / 2.0f) / static_cast<float>(anim.nSteps);
  anim.vStepSize =
      (g_logicalHeight<float> / 2.0f) / static_cast<float>(anim.nSteps);

  anim.fadingIn = true;
}

void end_level_fade_animation(entt::registry& registry,
                              const comp::level_faded_in_event& event)
{
  const auto entity = registry.create();
  registry.emplace<comp::level_switch_animation>(entity,
                                                 std::nullopt,
                                                 event.step,
                                                 event.nSteps,
                                                 event.hStepSize,
                                                 event.vStepSize,
                                                 false);
}

}  // namespace wanderer::sys::hud

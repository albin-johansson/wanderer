#include "level_switch_animation_system.hpp"

#include "components/graphics/level_switch_animation.hpp"
#include "core/game_constants.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float speed = 150;
inline constexpr float n_steps = 120;
inline constexpr cen::color gray{0x11, 0x11, 0x11};

}  // namespace

void update_level_switch_animations(entt::registry& registry,
                                    entt::dispatcher& dispatcher,
                                    const rune::delta_time dt)
{
  for (auto&& [entity, animation] : registry.view<comp::level_switch_animation>().each())
  {
    animation.width += animation.x_step_size * animation.speed * dt;
    animation.height += animation.y_step_size * animation.speed * dt;

    if (animation.fading_in)
    {
      if (animation.width >= glob::logical_width<float> / 2.0f)
      {
        dispatcher.enqueue<level_faded_in_event>(animation.map.value(),
                                                 animation.width,
                                                 animation.height,
                                                 -animation.x_step_size,
                                                 -animation.y_step_size);
      }
    }
    else
    {
      if (animation.width <= 0)
      {
        dispatcher.enqueue<level_faded_out_event>();
      }
    }
  }
}

void render_level_switch_animations(const entt::registry& registry,
                                    cen::renderer& renderer)
{
  for (auto&& [entity, animation] :
       registry.view<const comp::level_switch_animation>().each())
  {
    constexpr auto logicalSize = glob::logical_size<cen::farea>;
    constexpr auto width = logicalSize.width;
    constexpr auto height = logicalSize.height;

    const auto hSize = animation.width;
    const auto vSize = animation.height;
    renderer.set_color(gray);
    renderer.fill_rect(cen::rect(0.0f, 0.0f, width, vSize));
    renderer.fill_rect(cen::rect(0.0f, height - vSize, width, vSize));
    renderer.fill_rect(cen::rect(0.0f, 0.0f, hSize, height));
    renderer.fill_rect(cen::rect(width - hSize, 0.0f, hSize, height));
  }
}

void start_level_fade_animation(entt::registry& registry, const map_id map)
{
  auto& animation = registry.emplace<comp::level_switch_animation>(registry.create());
  animation.map = map;
  animation.speed = speed;
  animation.width = 0;
  animation.height = 0;
  animation.x_step_size = glob::logical_width<float> / n_steps;
  animation.y_step_size = glob::logical_height<float> / n_steps;
  animation.fading_in = true;
}

void end_level_fade_animation(entt::registry& registry, const level_faded_in_event& event)
{
  auto& animation = registry.emplace<comp::level_switch_animation>(registry.create());
  animation.map = std::nullopt;
  animation.speed = speed;
  animation.width = event.width;
  animation.height = event.height;
  animation.x_step_size = event.x_step_size;
  animation.y_step_size = event.y_step_size;
  animation.fading_in = false;
}

}  // namespace wanderer::sys

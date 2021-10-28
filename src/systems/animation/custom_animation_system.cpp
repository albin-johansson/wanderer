#include "custom_animation_system.hpp"

#include "components/custom_animation.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/custom_animation_halfway_event.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

constexpr float speed = 150;
constexpr float n_steps = 120;
constexpr cen::color gray{0x11, 0x11, 0x11};

}  // namespace

auto StartBondAnimation(entt::registry& registry, uint32 id) -> entt::entity
{
  const auto entity = registry.create();

  auto& animation = registry.emplace<comp::CustomAnimation>(entity);
  animation.id = id;
  animation.speed = speed;
  animation.width = 0;
  animation.height = 0;
  animation.x_step_size = glob::logical_width<float> / n_steps;
  animation.y_step_size = glob::logical_height<float> / n_steps;
  animation.fading_in = true;

  return entity;
}

auto StartReverseOnlyBondAnimation(entt::registry& registry) -> entt::entity
{
  const auto entity = registry.create();

  auto& animation = registry.emplace<comp::CustomAnimation>(entity);
  animation.speed = speed;
  animation.width = glob::logical_width<float> / 2.0f;
  animation.height = glob::logical_height<float> / 2.0f;
  animation.x_step_size = -glob::logical_width<float> / n_steps;
  animation.y_step_size = -glob::logical_height<float> / n_steps;
  animation.fading_in = false;

  return entity;
}

void UpdateCustomAnimations(entt::registry& registry,
                            entt::dispatcher& dispatcher,
                            float dt)
{
  for (auto&& [entity, animation] : registry.view<comp::CustomAnimation>().each()) {
    animation.width += animation.x_step_size * animation.speed * dt;
    animation.height += animation.y_step_size * animation.speed * dt;

    if (animation.fading_in && animation.width >= glob::logical_width<float> / 2.0f) {
      animation.x_step_size *= -1;
      animation.y_step_size *= -1;
      animation.fading_in = false;
      dispatcher.enqueue<CustomAnimationHalfwayEvent>(animation.id, entity);
    }
    else if (animation.width <= 0) {
      registry.destroy(entity);
    }
  }
}

void RenderCustomAnimations(const entt::registry& registry)
{
  constexpr auto width = glob::logical_width<float>;
  constexpr auto height = glob::logical_height<float>;

  auto& graphics = registry.ctx<ref<GraphicsContext>>().get();
  auto& renderer = graphics.get_renderer();
  for (auto&& [entity, animation] : registry.view<comp::CustomAnimation>().each()) {
    const auto hSize = animation.width;
    const auto vSize = animation.height;
    renderer.set_color(gray);
    renderer.fill_rect(cen::rect(0.0f, 0.0f, width, vSize));
    renderer.fill_rect(cen::rect(0.0f, height - vSize, width, vSize));
    renderer.fill_rect(cen::rect(0.0f, 0.0f, hSize, height));
    renderer.fill_rect(cen::rect(width - hSize, 0.0f, hSize, height));
  }
}

}  // namespace wanderer::sys

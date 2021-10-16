#include "viewport_system.hpp"

#include <cassert>  // assert

#include "common/ref.hpp"
#include "components/physics/movable.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float camera_speed = 10;

[[nodiscard]] auto next_camera_position(const float2 target,
                                        const ctx::viewport& viewport,
                                        const float dt) -> float2
{
  const auto boundsX = viewport.bounds.x();
  const auto boundsY = viewport.bounds.y();
  const auto boundsWidth = viewport.bounds.width();
  const auto boundsHeight = viewport.bounds.height();

  const auto distance = camera_speed * dt;

  const auto getX = [&](const float x) noexcept -> float {
    const auto value = boundsX + (x - boundsX) * distance;
    if (viewport.keep_in_bounds) {
      if (value < 0) {
        return 0;
      }
      else {
        const auto diff = viewport.level_size.width - boundsWidth;
        return (value > diff) ? diff : value;
      }
    }
    else {
      return value;
    }
  };

  const auto getY = [&](const float y) noexcept -> float {
    const auto value = boundsY + (y - boundsY) * distance;
    if (viewport.keep_in_bounds) {
      if (value < 0) {
        return 0;
      }
      else {
        const auto diff = viewport.level_size.height - boundsHeight;
        return (value > diff) ? diff : value;
      }
    }
    else {
      return value;
    }
  };

  return float2{getX(target.x), getY(target.y)};
}

[[nodiscard]] auto make_target(const float2 position,
                               const ctx::viewport& viewport) noexcept -> float2
{
  constexpr auto halfWidth = glob::humanoid_draw_width / 2.0f;
  constexpr auto halfHeight = glob::humanoid_draw_height / 2.0f;

  const auto halfBoundsWidth = viewport.bounds.width() / 2.0f;
  const auto halfBoundsHeight = viewport.bounds.height() / 2.0f;

  const auto x = (position.x + halfWidth) - halfBoundsWidth;
  const auto y = (position.y + halfHeight) - halfBoundsHeight;

  return {x, y};
}

void track(ctx::viewport& viewport, const float2 position, const float dt)
{
  const auto next = next_camera_position(make_target(position, viewport), viewport, dt);
  viewport.bounds.set_x(next.x);
  viewport.bounds.set_y(next.y);
}

}  // namespace

auto make_viewport(const cen::farea levelSize) noexcept -> ctx::viewport
{
  ctx::viewport viewport;

  viewport.bounds.set_size(glob::logical_size<cen::farea>);
  viewport.level_size = levelSize;

  return viewport;
}

void center_viewport_on(entt::registry& registry, const float2 position)
{
  auto& viewport = registry.ctx<ctx::viewport>();
  const auto target = make_target(position, viewport);
  viewport.bounds.set_x(target.x);
  viewport.bounds.set_y(target.y);
}

void update_viewport(entt::registry& registry, const entt::entity target, const float dt)
{
  assert(registry.all_of<comp::movable>(target));
  const auto& movable = registry.get<const comp::movable>(target);
  track(registry.ctx<ctx::viewport>(), movable.position, dt);
}

void translate_viewport(const entt::registry& registry)
{
  const auto& viewport = registry.ctx<ctx::viewport>();

  auto& gfx = registry.ctx<ref<graphics_context>>().get();
  auto& renderer = gfx.get_renderer();

  renderer.set_translation_viewport(viewport.bounds);
}

}  // namespace wanderer::sys

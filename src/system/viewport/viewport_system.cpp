#include "viewport_system.hpp"

#include "game_constants.hpp"
#include "movable.hpp"

namespace wanderer::sys {
namespace {

inline constexpr float cameraSpeed = 10.0f;

[[nodiscard]] auto next_camera_position(const vector2f& target,
                                        const comp::viewport& viewport,
                                        const delta_t dt) -> vector2f
{
  const auto boundsX = viewport.bounds.x();
  const auto boundsY = viewport.bounds.y();
  const auto boundsWidth = viewport.bounds.width();
  const auto boundsHeight = viewport.bounds.height();

  const auto distance = cameraSpeed * dt;

  const auto getX = [&](const float x) noexcept -> float {
    const auto value = boundsX + (x - boundsX) * distance;
    if (viewport.keepInBounds) {
      if (value < 0) {
        return 0;
      } else {
        const auto diff = viewport.levelSize.width - boundsWidth;
        return (value > diff) ? diff : value;
      }
    } else {
      return value;
    }
  };

  const auto getY = [&](const float y) noexcept -> float {
    const auto value = boundsY + (y - boundsY) * distance;
    if (viewport.keepInBounds) {
      if (value < 0) {
        return 0;
      } else {
        const auto diff = viewport.levelSize.height - boundsHeight;
        return (value > diff) ? diff : value;
      }
    } else {
      return value;
    }
  };

  return vector2f{getX(target.x), getY(target.y)};
}

[[nodiscard]] auto make_target_vector(const vector2f& position,
                                      const comp::viewport& viewport) noexcept
    -> vector2f
{
  constexpr auto halfWidth = glob::humanoid_draw_width / 2.0f;
  constexpr auto halfHeight = glob::humanoid_draw_height / 2.0f;

  const auto halfBoundsWidth = viewport.bounds.width() / 2.0f;
  const auto halfBoundsHeight = viewport.bounds.height() / 2.0f;

  const auto x = (position.x + halfWidth) - halfBoundsWidth;
  const auto y = (position.y + halfHeight) - halfBoundsHeight;

  return {x, y};
}

void track(comp::viewport& viewport, const vector2f& position, const delta_t dt)
{
  const auto next = next_camera_position(make_target_vector(position, viewport),
                                         viewport,
                                         dt);
  viewport.bounds.set_x(next.x);
  viewport.bounds.set_y(next.y);
}

}  // namespace

void center_viewport_on(entt::registry& registry,
                        comp::viewport::entity viewportEntity,
                        const vector2f& position)
{
  auto& viewport = registry.get<comp::viewport>(viewportEntity);
  const auto target = make_target_vector(position, viewport);
  viewport.bounds.set_x(target.x);
  viewport.bounds.set_y(target.y);
}

void update_viewport(level& level,
                     const entt::entity movableEntity,
                     const delta_t dt)
{
  const auto& movable = level.get<comp::movable>(movableEntity);
  track(level.get<comp::viewport>(level.viewport()), movable.position, dt);
}

void translate_renderer_viewport(const entt::registry& registry,
                                 comp::viewport::entity viewportEntity,
                                 cen::renderer& renderer)
{
  const auto& viewport = registry.get<comp::viewport>(viewportEntity);
  renderer.set_translation_viewport(viewport.bounds);
}

}  // namespace wanderer::sys

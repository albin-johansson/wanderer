#include "viewport_system.hpp"

#include "component/movable.hpp"
#include "game_constants.hpp"

namespace wanderer::sys::viewport {
namespace {

inline constexpr float g_cameraSpeed = 10.0f;

[[nodiscard]] auto next_camera_position(const vector2f& target,
                                        const comp::viewport& viewport,
                                        const delta dt) -> vector2f
{
  const auto boundsX = viewport.bounds.x();
  const auto boundsY = viewport.bounds.y();
  const auto boundsWidth = viewport.bounds.width();
  const auto boundsHeight = viewport.bounds.height();

  const auto distance = g_cameraSpeed * static_cast<float>(dt.get());

  const auto getX = [&](float x) noexcept -> float {
    const auto value = boundsX + (x - boundsX) * distance;
    if (value < 0) {
      return 0;
    } else {
      const auto diff = viewport.levelSize.width - boundsWidth;
      return (value > diff) ? diff : value;
    }
  };

  const auto getY = [&](float y) noexcept -> float {
    const auto value = boundsY + (y - boundsY) * distance;
    if (value < 0) {
      return 0;
    } else {
      const auto diff = viewport.levelSize.height - boundsHeight;
      return (value > diff) ? diff : value;
    }
  };

  return vector2f{getX(target.x()), getY(target.y())};
}

void track(comp::viewport& viewport, const vector2f& position, const delta dt)
{
  constexpr cen::farea size{g_humanoidDrawWidth, g_humanoidDrawHeight};

  const auto boundsWidth = viewport.bounds.width();
  const auto boundsHeight = viewport.bounds.height();

  const float targetX =
      (position.x() + (size.width / 2.0f)) - (boundsWidth / 2.0f);
  const float targetY =
      (position.y() + (size.height / 2.0f)) - (boundsHeight / 2.0f);

  const auto next = next_camera_position({targetX, targetY}, viewport, dt);

  viewport.bounds.set_x(next.x());
  viewport.bounds.set_y(next.y());
}

}  // namespace

void update(entt::registry& registry,
            const comp::viewport::entity viewportEntity,
            const entt::entity movableEntity,
            const delta dt)
{
  const auto& movable = registry.get<comp::movable>(movableEntity);
  auto& viewport = registry.get<comp::viewport>(viewportEntity.get());
  track(viewport, movable.position, dt);
}

void translate(entt::registry& registry,
               const comp::viewport::entity viewportEntity,
               cen::renderer& renderer)
{
  auto const& viewport = registry.get<comp::viewport>(viewportEntity.get());
  renderer.set_translation_viewport(viewport.bounds);
}

}  // namespace wanderer::sys::viewport

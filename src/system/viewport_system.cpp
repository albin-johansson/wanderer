#include "viewport_system.h"

#include "game_constants.h"
#include "movable.h"
#include "viewport.h"

using centurion::FArea;

namespace wanderer::system::viewport {
namespace {

void track(Viewport& viewport,
           const Vector2f& target,
           const FArea& size,
           const Delta delta)
{
  auto panSpeed = 15 * delta.get();

  const float targetX =
      (target.x + (size.width / 2.0f)) - (viewport.bounds.width() / 2.0f);

  const float targetY =
      (target.y + (size.height / 2.0f)) - (viewport.bounds.height() / 2.0f);

  const auto calc = [panSpeed](float targetPosComp,
                               float boundsPosComp,
                               float levelSizeComp,
                               float boundsSizeComp) noexcept -> float {
    float value = boundsPosComp + (targetPosComp - boundsPosComp) * panSpeed;
    if (value < 0) {
      value = 0;
    }
    const float diff = levelSizeComp - boundsSizeComp;
    value = (value > diff) ? diff : value;
    return value;
  };

  viewport.bounds.set_x(calc(targetX,
                             viewport.bounds.x(),
                             viewport.levelSize.width,
                             viewport.bounds.width()));
  viewport.bounds.set_y(calc(targetY,
                             viewport.bounds.y(),
                             viewport.levelSize.height,
                             viewport.bounds.height()));
}

}  // namespace

void update(entt::registry& registry,
            const ViewportEntity viewportEntity,
            const entt::entity playerEntity,
            const Delta delta)
{
  if (const auto* movable = registry.try_get<Movable>(playerEntity); movable) {
    if (auto* viewport = registry.try_get<Viewport>(viewportEntity.get());
        viewport) {
      track(*viewport,
            movable->interpolatedPos,
            {g_entityDrawWidth, g_entityDrawHeight},
            delta);
    }
  }
}

}  // namespace wanderer::system::viewport

#include "viewport_system.h"

#include "game_constants.h"
#include "movable.h"
#include "viewport.h"

using wanderer::component::Movable;
using wanderer::component::Viewport;

namespace wanderer::system::viewport {
namespace {

void track(Viewport& viewport,
           const Vector2f& target,
           const ctn::FArea& size,
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
            const Viewport::entity viewportEntity,
            const entt::entity movableEntity,
            const Delta delta)
{
  const auto& movable = registry.get<Movable>(movableEntity);
  auto& viewport = registry.get<Viewport>(viewportEntity.get());

  track(viewport,
        movable.interpolatedPos,
        {g_humanoidDrawWidth, g_humanoidDrawHeight},
        delta);
}

void translate(entt::registry& registry,
               const Viewport::entity viewportEntity,
               ctn::Renderer& renderer)
{
  auto const& viewport = registry.get<Viewport>(viewportEntity.get());
  renderer.set_translation_viewport(viewport.bounds);
}

}  // namespace wanderer::system::viewport

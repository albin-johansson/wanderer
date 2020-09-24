#include "viewport_system.hpp"

#include "component/movable.hpp"
#include "component/viewport.hpp"
#include "game_constants.hpp"

namespace wanderer::sys::viewport {
namespace {

void track(comp::viewport& viewport,
           const vector2f& target,
           const cen::farea& size,
           const delta dt)
{
  auto panSpeed = 15.0f * dt.get();

  const float targetX =
      (target.x() + (size.width / 2.0f)) - (viewport.bounds.width() / 2.0f);

  const float targetY =
      (target.y() + (size.height / 2.0f)) - (viewport.bounds.height() / 2.0f);

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
            const comp::viewport::entity viewportEntity,
            const entt::entity movableEntity,
            const delta dt)
{
  const auto& movable = registry.get<comp::movable>(movableEntity);
  auto& viewport = registry.get<comp::viewport>(viewportEntity.get());

  track(viewport,
        movable.position,
        {g_humanoidDrawWidth, g_humanoidDrawHeight},
        dt);
}

void translate(entt::registry& registry,
               const comp::viewport::entity viewportEntity,
               cen::renderer& renderer)
{
  auto const& viewport = registry.get<comp::viewport>(viewportEntity.get());
  renderer.set_translation_viewport(viewport.bounds);
}

}  // namespace wanderer::sys::viewport

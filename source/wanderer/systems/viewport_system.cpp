#include "viewport_system.hpp"

#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {
namespace {

constexpr float32 _camera_speed = 10;

}  // namespace

void update_render_bounds(entt::registry& registry)
{
  const auto& cfg = registry.ctx<game_cfg>();
  const auto& map = registry.ctx<comp::tilemap>();
  const auto& viewport = registry.ctx<comp::viewport>();

  const auto viewportMax = viewport.offset + viewport.size;

  /* Overwrite previous render bounds context */
  auto& bounds = registry.set<comp::render_bounds>();

  const auto min = viewport.offset / cfg.tile_size;
  bounds.begin_row = (min.y > 0) ? static_cast<usize>(min.y) : 0u;
  bounds.begin_col = (min.x > 0) ? static_cast<usize>(min.x) : 0u;

  const auto maxRow = static_cast<usize>(viewportMax.y / cfg.tile_size.y) + 1u;
  const auto maxCol = static_cast<usize>(viewportMax.x / cfg.tile_size.x) + 1u;
  bounds.end_row = (maxRow < map.row_count) ? maxRow : map.row_count;
  bounds.end_col = (maxCol < map.col_count) ? maxCol : map.col_count;
}

void update_viewport(entt::registry& registry, const float32 dt)
{
  const auto& map = registry.ctx<const comp::tilemap>();
  auto& viewport = registry.ctx<comp::viewport>();

  /* Don't move the viewport if there is no viewport target */
  const auto view = registry.view<comp::viewport_target>();
  if (view.empty()) {
    return;
  }

  WANDERER_ASSERT_MSG(view.size() == 1, "There cannot be more than 1 viewport target!");
  const auto targetEntity = view.front();

  WANDERER_ASSERT(registry.all_of<comp::game_object>(targetEntity));
  const auto& object = registry.get<comp::game_object>(targetEntity);

  const auto target = (object.position + (object.size / 2.0f)) - (viewport.size / 2.0f);
  auto next = viewport.offset + (target - viewport.offset) * (_camera_speed * dt);

  if (viewport.keep_in_bounds) {
    next.x = (next.x < 0) ? 0 : next.x;
    next.y = (next.y < 0) ? 0 : next.y;

    const auto diff = map.size - viewport.size;
    next.x = (next.x > diff.x) ? diff.x : next.x;
    next.y = (next.y > diff.y) ? diff.y : next.y;
  }

  viewport.offset = next;
}

}  // namespace wanderer::sys
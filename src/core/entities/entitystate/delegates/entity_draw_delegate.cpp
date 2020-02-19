#include "entity_draw_delegate.h"

#include <rectangle.h>
#include <renderer.h>

#include "entity.h"
#include "viewport.h"

using namespace centurion;
using namespace centurion::video;
using namespace centurion::math;

namespace albinjohansson::wanderer {

void EntityDrawDelegate::draw(const Renderer& renderer,
                              const IEntity& entity,
                              int srcX,
                              int srcY) noexcept
{
  const auto& [x, y] = entity.get_interpolated_position();
  const auto src = IRect{srcX, srcY, 64, 64};
  const auto dst = FRect{x, y, entity.get_width(), entity.get_height()};
  renderer.render_tf(entity.get_sprite_sheet(), src, dst);
}

}  // namespace albinjohansson::wanderer

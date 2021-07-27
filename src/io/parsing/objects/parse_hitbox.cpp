#include "parse_hitbox.hpp"

#include "core/aliases/float2.hpp"
#include "systems/movement/hitbox_system.hpp"

namespace wanderer::io {

auto parse_hitbox(const rune::tmx_object& object, const float xRatio, const float yRatio)
    -> comp::hitbox
{
  const auto pos = float2{object.x * xRatio, object.y * yRatio};
  const auto size = cen::farea{object.width * xRatio, object.height * yRatio};

  const comp::subhitbox subhitbox{{}, size};

  auto hitbox = sys::make_hitbox({subhitbox});
  hitbox.enabled = false;

  sys::set_position(hitbox, pos);

  return hitbox;
}

}  // namespace wanderer::io

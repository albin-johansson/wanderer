#include "parse_hitbox.hpp"

#include "systems/physics/hitbox_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer::io {

auto parse_hitbox(const rune::tmx_object& object, const float xRatio, const float yRatio)
    -> comp::Hitbox
{
  const auto pos = float2{object.x * xRatio, object.y * yRatio};
  const auto size = cen::farea{object.width * xRatio, object.height * yRatio};

  const comp::Subhitbox subhitbox{{}, size};

  auto hitbox = sys::MakeHitbox({subhitbox});
  hitbox.enabled = false;

  sys::SetPosition(hitbox, pos);

  return hitbox;
}

}  // namespace wanderer::io

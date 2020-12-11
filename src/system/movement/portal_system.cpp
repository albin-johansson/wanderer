#include "portal_system.hpp"

#include "component/hitbox.hpp"
#include "component/portal.hpp"
#include "hitbox_system.hpp"

namespace wanderer::sys::portal {


void update(entt::registry& registry, const comp::player::entity player)
{
  const auto& hitbox = registry.get<comp::hitbox>(player.get());
  registry.view<comp::portal, comp::hitbox>().each(
      [&](const entt::entity e, const comp::portal& portal, comp::hitbox& hb) {
        hb.enabled = true;

        if (sys::hitbox::intersects(hitbox, hb)) {
          registry.emplace_or_replace<comp::is_within_portal>(player, e);
        } else if (const auto* iwp =
                       registry.try_get<comp::is_within_portal>(player)) {
          if (iwp->portal == e) {
            registry.remove<comp::is_within_portal>(player);
          }
        }

        hb.enabled = false;
      });
}

}  // namespace wanderer::sys::portal

#include "portal_system.hpp"

#include "hitbox.hpp"
#include "hitbox_system.hpp"
#include "portal.hpp"

namespace wanderer::sys::portal {

void update(entt::registry& registry, const comp::player::entity player)
{
  const auto& playerHitbox = registry.get<comp::hitbox>(player);
  const auto view = registry.view<comp::portal, comp::hitbox>();
  view.each([&](const entt::entity e,
                const comp::portal& portal,
                comp::hitbox& hitbox) {
    hitbox.enabled = true;

    if (sys::hitbox::intersects(playerHitbox, hitbox)) {
      registry.emplace_or_replace<comp::is_within_portal>(player, e);

    } else if (const auto* iwp =
                   registry.try_get<comp::is_within_portal>(player)) {
      if (iwp->portal == e) {
        registry.remove<comp::is_within_portal>(player);
      }
    }

    hitbox.enabled = false;
  });
}

}  // namespace wanderer::sys::portal

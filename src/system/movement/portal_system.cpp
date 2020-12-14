#include "portal_system.hpp"

#include "portal.hpp"
#include "update_triggers.hpp"

namespace wanderer::sys::portal {

void update_triggers(entt::registry& registry, comp::player::entity player)
{
  const auto removePredicate =
      [](const comp::is_within_portal& isWithinTrigger,
         const comp::portal::entity portalEntity) noexcept {
        return isWithinTrigger.portalEntity == portalEntity;
      };

  sys::update_triggers<comp::portal, comp::is_within_portal>(registry,
                                                             player,
                                                             removePredicate);
}

}  // namespace wanderer::sys::portal

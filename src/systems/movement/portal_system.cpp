#include "portal_system.hpp"

#include "portal.hpp"
#include "update_triggers.hpp"

namespace wanderer::sys {

void update_portal_triggers(entt::registry& registry,
                            const comp::player::entity player)
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

}  // namespace wanderer::sys

#include "translation_viewport_system.h"

#include "viewport.h"

using namespace centurion;

namespace wanderer {

void update_translation_viewport(entt::registry& registry,
                                 const entt::entity viewport,
                                 Renderer& renderer)
{
  if (const auto* view = registry.try_get<Viewport>(viewport); view) {
    renderer.set_translation_viewport(view->bounds());
  }
}

}  // namespace wanderer

#include "make_map.h"

#include <step.h>

using namespace centurion;

namespace wanderer {

entt::entity make_map(entt::registry& registry,
                      std::string_view map,
                      Renderer& renderer)
{
  const auto stepMap{step::parse("resource/map/", map)};
  const auto entity{registry.create()};

  return entity;
}

}  // namespace wanderer

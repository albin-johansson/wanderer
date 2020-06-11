#pragma once

#include <step.h>

#include <vector>

#include "types.h"

namespace wanderer {

entt::entity make_tileset(entt::registry& registry,
                          const std::vector<step::Tileset>& tilesets);

}

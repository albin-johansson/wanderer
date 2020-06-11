#pragma once

#include <step.h>

#include "types.h"

namespace wanderer {

entt::entity make_tile(entt::registry& registry, const step::Tile& stepTile);

}

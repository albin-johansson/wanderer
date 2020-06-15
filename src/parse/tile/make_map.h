#pragma once

#include <renderer.h>

#include <string_view>

#include "types.h"

namespace wanderer {

[[nodiscard]] entt::entity make_map(entt::registry& registry,
                                    std::string_view map,
                                    centurion::Renderer& renderer);

}

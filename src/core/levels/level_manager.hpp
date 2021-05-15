#pragma once

#include <entt.hpp>    // registry, entity
#include <filesystem>  // path
#include <utility>     // forward

#include "components/map/level.hpp"
#include "core/aliases/map_id.hpp"
#include "core/aliases/maybe.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/saves/save_file_info.hpp"

namespace wanderer {

class [[deprecated]] level_manager final
{
 public:
  level_manager(entt::registry& shared, graphics_context& graphics);

  void switch_to(map_id id);
};

}  // namespace wanderer

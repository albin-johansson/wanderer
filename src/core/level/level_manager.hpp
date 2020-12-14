#pragma once

#include <memory>         // unique_ptr
#include <unordered_map>  // unordered_map

#include "graphics_context.hpp"
#include "level.hpp"
#include "map_id.hpp"
#include "maybe.hpp"

namespace wanderer {

class level_manager final
{
 public:
  level_manager(graphics_context& graphics);

  void enable_world();

  void switch_to(map_id id);

  [[nodiscard]] auto current() noexcept -> level*;

 private:
  std::unordered_map<map_id, std::unique_ptr<level>> m_levels;
  maybe<map_id> m_current;
  maybe<map_id> m_world;
};

}  // namespace wanderer

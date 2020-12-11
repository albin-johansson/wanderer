#pragma once

#include <cen/renderer.hpp>
#include <memory>  // unique_ptr
#include <unordered_map>  // unordered_map

#include "level.hpp"
#include "texture_cache.hpp"
#include "map_id.hpp"
#include "maybe.hpp"

namespace wanderer {

class level_manager final
{
 public:
  level_manager(cen::renderer& renderer, texture_cache& cache);

  void enable_world();

  void switch_to(map_id id);

  [[nodiscard]] auto current() noexcept -> level*;

 private:
  std::unordered_map<map_id, std::unique_ptr<level>> m_levels;
  maybe<map_id> m_current;
  maybe<map_id> m_world;
};

}  // namespace wanderer

#pragma once

#include <entt.hpp>       // registry, entity
#include <filesystem>     // path
#include <memory>         // unique_ptr
#include <unordered_map>  // unordered_map
#include <utility>        // forward

#include "core/aliases/map_id.hpp"
#include "core/aliases/maybe.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/levels/level.hpp"
#include "io/saves/save_file_info.hpp"

namespace wanderer {

class level_manager final
{
 public:
  explicit level_manager(graphics_context& graphics);

  level_manager(const save_file_info& info, graphics_context& graphics);

  void switch_to(map_id id);

  [[nodiscard]] auto registry() -> entt::registry&;

  [[nodiscard]] auto registry() const -> const entt::registry&;

  [[nodiscard]] auto current() noexcept -> level&;

  [[nodiscard]] auto current() const noexcept -> const level&;

  [[nodiscard]] auto world() const -> map_id;

  [[nodiscard]] auto current_id() const -> map_id;

  [[nodiscard]] auto begin() const noexcept
  {
    return m_levels.begin();
  }

  [[nodiscard]] auto end() const noexcept
  {
    return m_levels.end();
  }

 private:
  std::unordered_map<map_id, std::unique_ptr<level>> m_levels;
  maybe<map_id> m_current;
  maybe<map_id> m_world;
};

}  // namespace wanderer

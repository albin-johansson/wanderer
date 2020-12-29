#pragma once

#include <memory>         // unique_ptr
#include <unordered_map>  // unordered_map
#include <utility>        // forward

#include "graphics_context.hpp"
#include "level.hpp"
#include "map_id.hpp"
#include "maybe.hpp"

namespace wanderer {

class level_manager final
{
 public:
  explicit level_manager(graphics_context& graphics);

  void enable_world();

  void switch_to(map_id id);

  template <typename Component>
  void clear()
  {
    current()->template clear<Component>();
  }

  template <typename Component, typename... Args>
  decltype(auto) emplace(entt::entity e, Args&&... args)
  {
    current()->template emplace<Component>(e, std::forward<Args>(args)...);
  }

  [[nodiscard]] auto registry() -> entt::registry&;

  [[nodiscard]] auto registry() const -> const entt::registry&;

  [[nodiscard]] auto current() noexcept -> level*;

  [[nodiscard]] auto current() const noexcept -> const level*;

 private:
  std::unordered_map<map_id, std::unique_ptr<level>> m_levels;
  maybe<map_id> m_current;
  maybe<map_id> m_world;
};

}  // namespace wanderer

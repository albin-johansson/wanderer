#pragma once

#include <cen/area.hpp>
#include <cen/rect.hpp>
#include <entt.hpp>
#include <named_type.hpp>

namespace wanderer::comp {
namespace detail {
struct viewport_entity_t;
}

/**
 * @struct viewport
 * @brief Represents an area that is visible for the player.
 *
 * @var viewport::bounds
 * The position and size of the viewport.
 * @var viewport::levelSize
 * The size of the level that the viewport is associated with.
 *
 * @headerfile viewport.hpp
 */
struct viewport final
{
  using entity = fluent::
      NamedType<entt::entity, detail::viewport_entity_t, fluent::Comparable>;
  cen::frect bounds{};
  cen::farea levelSize{};
};

}  // namespace wanderer::comp

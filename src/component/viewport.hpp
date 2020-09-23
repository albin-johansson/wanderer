#pragma once

#include <area.hpp>
#include <rect.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

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
      NamedType<entt::entity, struct ViewportEntityTag, fluent::Comparable>;
  cen::frect bounds{};
  cen::farea levelSize{};
};

}  // namespace wanderer::comp

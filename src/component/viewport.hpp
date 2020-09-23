/**
 * @brief Provides the `Viewport` component.
 * @file viewport.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <area.hpp>
#include <rect.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @struct Viewport
 * @brief Represents an area that is visible for the player.
 *
 * @var Viewport::bounds
 * The position and size of the viewport.
 * @var Viewport::levelSize
 * The size of the level that the viewport is associated with.
 *
 * @headerfile viewport.hpp
 */
struct Viewport final
{
  using entity = fluent::
      NamedType<entt::entity, struct ViewportEntityTag, fluent::Comparable>;
  cen::frect bounds{};
  cen::farea levelSize{};
};

}  // namespace wanderer::comp

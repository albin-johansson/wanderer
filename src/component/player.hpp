#pragma once

#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct player_entity_t;
}

/**
 * \struct player
 *
 * \brief A tag type used to identify the player.
 *
 * \headerfile player.hpp
 */
struct player
{
  using entity = entity_type<detail::player_entity_t>;
};

}  // namespace wanderer::comp
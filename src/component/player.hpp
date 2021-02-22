#pragma once

#include "entity_type.hpp"
#include "ints.hpp"

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
struct player final
{
  using entity = entity_type<detail::player_entity_t>;
};

template <typename Archive>
void serialize(Archive&, player&, u32 version)
{}

}  // namespace wanderer::comp
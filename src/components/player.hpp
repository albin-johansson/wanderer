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
  using entity [[deprecated]] = entity_type<detail::player_entity_t>;

  entt::entity playerEntity{entt::null};
};

template <typename Archive>
void serialize(Archive& archive, player& p, u32 version)
{
  archive(p.playerEntity);
}

}  // namespace wanderer::comp
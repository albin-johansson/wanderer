#pragma once

namespace wanderer::core {

/**
 * The EntityStateID enum class provides values that serve as identifiers (or keys) for the various
 * possible entity states.
 *
 * @since 0.1.0
 */
enum class EntityStateID {
  IDLE,
  WALK,
  ATTACK,
  DIE
};

}

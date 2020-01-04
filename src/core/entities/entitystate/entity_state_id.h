#pragma once

namespace albinjohansson::wanderer {

/**
 * The EntityStateID enum class provides values that serve as identifiers (or keys) for the various
 * possible entity states.
 *
 * @since 0.1.0
 */
enum class EntityStateID {
  Idle,
  Walk,
  Attack,
  Die
};

}

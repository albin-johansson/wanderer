#pragma once
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

/**
 * The GameObjectID class is a simple class that is used to obtain game object
 * IDs that are unique.
 *
 * @since 0.1.0
 */
class GameObjectID final {
 private:
  static uint64 count;

 public:
  GameObjectID() = delete;

  ~GameObjectID() = default;

  /**
   * Returns a new unique game object ID.
   *
   * @return a new unique game object ID.
   * @since 0.1.0
   */
  [[nodiscard]] static uint64 next() noexcept;

  /**
   * Returns the last generated game object ID.
   *
   * @return the last generated game object ID.
   * @since 0.1.0
   */
  [[nodiscard]] static uint64 peek() noexcept;
};

}  // namespace albinjohansson::wanderer

#pragma once
#include "direction.h"

namespace wanderer {

/**
 * The EntitySheet class is a utility for calculating the correct source
 * coordinate in an entity sprite sheet when rendering an entity.
 *
 * @since 0.1.0
 */
class EntitySheet final {
 public:
  EntitySheet() = delete;

  ~EntitySheet() = default;

  /**
   * Calculates and returns the source y-coordinate for the supplied origin
   * coordinate and direction.
   *
   * @param y the origin y-coordinate in the entity sheet.
   * @param direction the dominant direction of the entity.
   * @return the source y-coordinate in the entity sheet.
   * @since 0.1.0
   */
  [[nodiscard]] static int get_source_y(int y, Direction direction) noexcept;
};

}  // namespace wanderer

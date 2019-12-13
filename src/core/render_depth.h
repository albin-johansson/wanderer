#pragma once

namespace albinjohansson::wanderer {

/**
 * The RenderDepth struct contains constants for the possible render depths.
 *
 * @since 0.1.0
 */
struct RenderDepth final {
  /**
   * The least possible render depth value.
   *
   * @since 0.1.0
   */
  static constexpr int MIN = 0;

  /**
   * The highest possible render depth value.
   *
   * @since 0.1.0
   */
  static constexpr int MAX = 9;

  /**
   * The amount of possible render depth values.
   *
   * @since 0.1.0
   */
  static constexpr int RANGE = MAX + 1;

  RenderDepth() = delete;

  ~RenderDepth() = default;
};

}

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
  static constexpr int min = 0;

  /**
   * The highest possible render depth value.
   *
   * @since 0.1.0
   */
  static constexpr int max = 9;

  /**
   * The amount of possible render depth values.
   *
   * @since 0.1.0
   */
  static constexpr int range = max + 1;

  RenderDepth() = delete;

  ~RenderDepth() = default;
};

}  // namespace albinjohansson::wanderer

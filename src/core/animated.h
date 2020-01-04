#pragma once
#include <cstdint>

namespace centurion {

class Image;

}

namespace albinjohansson::wanderer {

/**
 * The IAnimated interface specifies objects that can be animated.
 *
 * @since 0.1.0
 */
class IAnimated {
 public:
  virtual ~IAnimated() = default;

  /**
   * Updates the state of the animation.
   *
   * @since 0.1.0
   */
  virtual void update_animation() noexcept = 0;

  /**
   * Sets the current animation frame by index. An invalid index will be clamped to the closest
   * legal value.
   *
   * @param index the index of the desired animation frame (zero-indexed).
   * @since 0.1.0
   */
  virtual void set_animation_frame(int index) noexcept = 0;

  /**
   * Sets the amount of animation frames that will be iterated by the animation.
   *
   * @param nFrames the number of animation frames, must be greater than zero.
   * @since 0.1.0
   */
  virtual void set_animation_frame_amount(int nFrames) = 0;

  /**
   * Sets the delay in between frames.
   *
   * @param ms the delay in between frames, in milliseconds.
   * @since 0.1.0
   */
  virtual void set_animation_delay(uint32_t ms) = 0;

  /**
   * Returns the index of the currently active animation frame.
   *
   * @return the index of the currently active animation frame.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual int get_animation_frame() const noexcept = 0;

  /**
   * Indicates whether or not the animation is "done", the animation is considered done every
   * time the index corresponds to the final animation frame.
   *
   * @return true if the animation index is equal to the index of the final frame; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual bool is_animation_done() const noexcept = 0;

  /**
   * Returns a reference to the internal sprite sheet.
   *
   * @return a reference to the internal sprite sheet.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual centurion::Image& get_sprite_sheet() const noexcept = 0;
};

}

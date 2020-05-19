#pragma once
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

/**
 * The Animation class represents an arbitrary animation of a set of frames.
 *
 * @since 0.1.0
 */
class Animation final {
 private:
  int nFrames = 1;
  int index = 0;
  uint32 delay = 100;
  uint32 previous = 0;

 public:
  Animation() noexcept;

  ~Animation() noexcept;

  /**
   * Updates the state of the animation.
   *
   * @since 0.1.0
   */
  void update() noexcept;

  /**
   * Resets the state of the animation.
   *
   * @since 0.1.0
   */
  void reset() noexcept;

  /**
   * Sets the time in between frames, in milliseconds.
   *
   * @param delay the time in between frames, in milliseconds.
   * @since 0.1.0
   */
  void set_delay(uint32 delay) noexcept;

  /**
   * Sets the currently active frame. An invalid frame index will be clamped to
   * match the closest valid index.
   *
   * @param frameIndex the index of the frame that will be made active.
   * @since 0.1.0
   */
  void set_frame(int frameIndex) noexcept;

  /**
   * Sets the number of frames in the animation. This method has no effect if
   * the supplied number of frames isn't greater than zero.
   *
   * @param nFrames the number of frames.
   * @since 0.1.0
   */
  void set_number_of_frames(int nFrames) noexcept;

  /**
   * Returns the currently active frame index.
   *
   * @return the currently active frame index.
   * @since 0.1.0
   */
  [[nodiscard]] int get_index() const noexcept;

  /**
   * Indicates whether or not the animation has reached the final frame.
   *
   * @return true if the animation has reached the final frame; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool is_done() const noexcept;
};

}  // namespace albinjohansson::wanderer

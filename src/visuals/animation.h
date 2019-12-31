#pragma once
#include <cstdint>

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
  uint32_t delay = 100;
  uint32_t previous = 0;

 public:
  Animation() noexcept;

  ~Animation() noexcept;

  /**
   * Updates the state of the animation.
   *
   * @since 0.1.0
   */
  void Update() noexcept;

  /**
   * Resets the state of the animation.
   *
   * @since 0.1.0
   */
  void Reset() noexcept;

  /**
   * Sets the time in between frames, in milliseconds.
   *
   * @param delay the time in between frames, in milliseconds.
   * @since 0.1.0
   */
  void SetDelay(uint32_t delay) noexcept;

  /**
   * Sets the currently active frame. An invalid frame index will be clamped to match the closest
   * valid index.
   *
   * @param frameIndex the index of the frame that will be made active.
   * @since 0.1.0
   */
  void SetFrame(int frameIndex) noexcept;

  /**
   * Sets the number of frames in the animation. This method has no effect if the supplied number
   * of frames isn't greater than zero.
   *
   * @param nFrames the number of frames.
   * @since 0.1.0
   */
  void SetNumberOfFrames(int nFrames) noexcept;

  /**
   * Returns the currently active frame index.
   *
   * @return the currently active frame index.
   * @since 0.1.0
   */
  [[nodiscard]]
  int GetIndex() const noexcept;

  /**
   * Indicates whether or not the animation has reached the final frame.
   *
   * @return true if the animation has reached the final frame; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool IsDone() const noexcept;
};

}

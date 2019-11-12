#pragma once
#include <SDL_timer.h>

namespace wanderer::visuals {

/**
 * The Animation class represents an arbitrary animation of a set of frames.
 *
 * @since 0.1.0
 */
class Animation final {
 private:
  int nFrames;
  int index;
  Uint32 delay;
  Uint32 previous;

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
  void SetDelay(Uint32 delay) noexcept;

  /**
   * Sets the currently active frame. An invalid frame index will be clamped to match the closest
   * valid index.
   *
   * @param frameIndex the index of the frame that will be made active.
   * @since 0.1.0
   */
  void SetFrame(int frameIndex) noexcept;

  /**
   * Sets the number of frames in the animation.
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
  [[nodiscard]] inline int GetIndex() const noexcept {
    return index;
  }
};

}

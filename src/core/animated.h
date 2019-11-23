#pragma once
#include <SDL_types.h>
#include "image.h"

namespace albinjohansson::wanderer {

/**
 * The IAnimated interface specifies objects that can be animated.
 *
 * @since 0.1.0
 */
class IAnimated {
 protected:
  IAnimated() = default;

 public:
  virtual ~IAnimated() = default;

  /**
   * Updates the state of the animation.
   *
   * @since 0.1.0
   */
  virtual void UpdateAnimation() noexcept = 0;

  /**
   * Sets the current animation frame by index. An invalid index will be clamped to the closest
   * legal value.
   *
   * @param index the index of the desired animation frame (zero-indexed).
   * @since 0.1.0
   */
  virtual void SetAnimationFrame(int index) noexcept = 0;

  /**
   * Sets the amount of animation frames that will be iterated by the animation.
   *
   * @param nFrames the number of animation frames, must be greater than zero.
   * @since 0.1.0
   */
  virtual void SetAnimationFrameAmount(int nFrames) = 0;

  /**
   * Sets the delay in between frames.
   *
   * @param ms the delay in between frames, in milliseconds.
   * @since 0.1.0
   */
  virtual void SetAnimationDelay(Uint32 ms) = 0;

  /**
   * Returns the index of the currently active animation frame.
   *
   * @return the index of the currently active animation frame.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetAnimationFrame() const noexcept = 0;

  /**
   * Indicates whether or not the animation is "done", the animation is considered done every
   * time the index corresponds to the final animation frame.
   *
   * @return true if the animation index is equal to the index of the final frame; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] virtual bool IsAnimationDone() const noexcept = 0;

  /**
   * Returns a reference to the internal sprite sheet.
   *
   * @return a reference to the internal sprite sheet.
   * @since 0.1.0
   */
  [[nodiscard]] virtual Image& GetSpriteSheet() const noexcept = 0;

};

}

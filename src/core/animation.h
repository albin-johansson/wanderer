#pragma once

#include "types.h"

namespace wanderer {

/**
 * The Animation class represents the logic of keeping track of the
 * state of an animation.
 */
class Animation final {
 public:
  /**
   * Updates the state of the animation.
   */
  void tick() noexcept;

  /**
   * Resets the state of the animation.
   */
  void reset() noexcept;

  /**
   * Sets the delay of the animation, this is the time that each frame is
   * active.
   *
   * @param delay the duration of each frame in the animation, in milliseconds.
   */
  void set_delay(u32 delay) noexcept;

  /**
   * Sets the number of frames in the animation.
   *
   * @param frames the number of frames in the animation.
   */
  void set_frames(u32 frames) noexcept;

  /**
   * Returns the currently active frame of the animation.
   *
   * @return the index of the currently active frame of the animation.
   */
  [[nodiscard]] u32 frame() const noexcept { return m_frame; }

  /**
   * Returns the number of frames in the animation.
   *
   * @return the number of frames in the animation.
   */
  [[nodiscard]] u32 frames() const noexcept { return m_nFrames; }

  /**
   * Returns the delay of the animation (the duration of each frame).
   *
   * @return the duration of each frame, in milliseconds.
   */
  [[nodiscard]] u32 delay() const noexcept { return m_delay; }

 private:
  u32 m_frame{0};
  u32 m_nFrames{1};
  u32 m_then{0};
  u32 m_delay{100};
};

}  // namespace wanderer

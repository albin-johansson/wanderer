#pragma once
#include <key_state.h>
#include <mouse_state.h>

#include <memory>

#include "game_loop.h"
#include "input.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

/**
 * The SmoothFixedTimestepLoop class represents a fixed timestep game loop that
 * uses delta time smoothing and interpolation. Note! This game loop assumes
 * that VSync is enabled.
 *
 * @since 0.1.0
 */
class SmoothFixedTimestepLoop final : public IGameLoop {
 public:
  /**
   * @param keyState the associated key state instance.
   * @param mouseState the associated mouse state instance.
   * @param vsyncRate the vsync rate, in Hz.
   * @throws NullPointerException if any pointers are null.
   * @since 0.1.0
   */
  SmoothFixedTimestepLoop(
      UniquePtr<centurion::input::KeyState> keyState,
      const SharedPtr<centurion::input::MouseState>& mouseState,
      float vsyncRate);

  ~SmoothFixedTimestepLoop() override;

  void update(IWandererCore& core, ctn::Renderer& renderer) override;

 private:
  /**
   * A constant that denotes the maximum allowed frame time (delta time) in
   * seconds. This is used to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  static constexpr float maxFrameTime = 0.25f;

  UniquePtr<Input> m_input = nullptr;

  uint64 m_then = 0;
  uint64 m_now = 0;
  const float m_vsyncRate;
  const float m_timeStep;
  const float m_counterFreq;
  float m_accumulator = 0;
  float m_delta = 0;
  float m_deltaBuffer = 0;

  /**
   * Updates the input state.
   *
   * @param core a reference to the associated core model.
   * @param windowWidth the current width of the window.
   * @param windowHeight the current height of the window.
   * @since 0.1.0
   */
  void update_input(IWandererCore& core, int windowWidth, int windowHeight);

  /**
   * Smoothes the current delta value.
   *
   * @since 0.1.0
   */
  void smooth_delta();
};

}  // namespace albinjohansson::wanderer

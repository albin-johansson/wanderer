#pragma once
#include "game_loop.h"
#include "input.h"
#include <memory>
#include <cstdint>

namespace albinjohansson::wanderer {

/**
 * The SmoothFixedTimestepLoop class represents a fixed timestep game loop that uses delta time
 * smoothing and interpolation. Note! This game loop assumes that VSync is enabled.
 *
 * @since 0.1.0
 */
class SmoothFixedTimestepLoop final : public IGameLoop {
 private:
  /**
   * A constant that denotes the maximum allowed frame time (delta time) in seconds. This is used
   * to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  static constexpr float maxFrameTime = 0.25f;

  std::unique_ptr<Input> input = nullptr;

  uint32_t then = 0;
  uint32_t now = 0;
  const float vsyncRate;
  const float timeStep;
  const float counterFreq;
  float accumulator = 0;
  float delta = 0;
  float deltaBuffer = 0;

  /**
   * Updates the input state.
   *
   * @param core a reference to the associated core model.
   * @since 0.1.0
   */
  void update_input(IWandererCore& core);

  /**
   * Smoothes the current delta value.
   *
   * @since 0.1.0
   */
  void smooth_delta();

 public:
  /**
   * @param keyStateManager the associated key state manager.
   * @param mouseStateManager the associated mouse state manager.
   * @param vsyncRate the vsync rate, in Hz.
   * @throws NullPointerException if any pointers are null.
   * @since 0.1.0
   */
  SmoothFixedTimestepLoop(std::unique_ptr<KeyStateManager> keyStateManager,
                          std::unique_ptr<MouseStateManager> mouseStateManager,
                          float vsyncRate);

  ~SmoothFixedTimestepLoop() override;

  void update(IWandererCore& core, centurion::Renderer& renderer) override;
};

}

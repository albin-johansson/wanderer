#pragma once
#include "game_loop.h"
#include <memory>
#include <cstdint>

namespace albinjohansson::wanderer {

class KeyStateManager;
class MouseStateManager;

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
  static constexpr float MAX_FRAME_TIME = 0.25f;

  std::shared_ptr<KeyStateManager> keyStateManager = nullptr;
  std::shared_ptr<MouseStateManager> mouseStateManager = nullptr;

  uint32_t then = 0;
  uint32_t now = 0;
  const float timeStep;
  const float counterFreq;
  const float vsyncRate;
  float accumulator = 0;
  float delta = 0;
  float deltaBuffer = 0;

  /**
   * Updates the input state.
   *
   * @param core a reference to the associated core model.
   * @since 0.1.0
   */
  void UpdateInput(IWandererCore& core);

  /**
   * Smoothes the current delta value.
   *
   * @since 0.1.0
   */
  void SmoothDelta();

 public:
  /**
   * @param keyStateManager the associated key state manager.
   * @param mouseStateManager the associated mouse state manager.
   * @param vsyncRate the vsync rate, in Hz.
   * @throws NullPointerException if any pointers are null.
   * @since 0.1.0
   */
  SmoothFixedTimestepLoop(const std::shared_ptr<KeyStateManager>& keyStateManager,
                          const std::shared_ptr<MouseStateManager>& mouseStateManager,
                          float vsyncRate);

  ~SmoothFixedTimestepLoop() override;

  void Update(IWandererCore& core, Renderer& renderer) override;
};

}

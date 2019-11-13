#pragma once
#include "game_loop.h"
#include "wanderer_core.h"
#include "renderer.h"
#include "key_state_manager.h"
#include <SDL_types.h>

namespace wanderer::controller {

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

  /**
   * A constant that represents the size of the fixed time steps, in seconds.
   *
   * @since 0.1.0
   */
  static constexpr float FIXED_TIME_STEP = 1.0f / 60.0f;

  KeyStateManager_sptr keyStateManager = nullptr;
  Uint32 then = 0;
  Uint32 now = 0;
  float vsyncRate = 0;
  float accumulator = 0;
  float delta = 0;
  bool quit = false;

  /**
   * Updates the input state.
   *
   * @param core a reference to the associated core model.
   * @since 0.1.0
   */
  void UpdateInput(core::IWandererCore& core);

  /**
   * Smoothes the current delta value.
   *
   * @since 0.1.0
   */
  void SmoothDelta();

 public:
  /**
   * @param keyStateManager a shared pointer to the associated key state manager.
   * @param vsyncRate the vsync rate, in Hz.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  SmoothFixedTimestepLoop(KeyStateManager_sptr keyStateManager, float vsyncRate);

  ~SmoothFixedTimestepLoop() override;

  void Update(core::IWandererCore& core, visuals::Renderer& renderer) override;

  [[nodiscard]] inline bool ShouldQuit() const noexcept override {
    return quit;
  }
};

}

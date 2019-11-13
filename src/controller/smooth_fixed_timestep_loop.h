#pragma once
#include "wanderer_core.h"
#include "renderer.h"
#include "key_state_manager.h"
#include <SDL_types.h>

namespace wanderer::controller {

/**
 * The SmoothFixedTimestepLoop class represents a fixed timestep game loop that uses delta time
 * smoothing and interpolation.
 *
 * @since 0.1.0
 */
class SmoothFixedTimestepLoop final {
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

  void UpdateInput(core::IWandererCore& core);

  void SmoothDelta();

 public:
  /**
   * @param keyStateManager a shared pointer to the associated key state manager.
   * @param vsyncRate the vsync rate, in Hz.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  SmoothFixedTimestepLoop(KeyStateManager_sptr keyStateManager, float vsyncRate);

  ~SmoothFixedTimestepLoop();

  /**
   * Updates the state of the loop.
   *
   * @param core a reference to the wanderer core that will be updated.
   * @param renderer a reference to the renderer that will be used.
   * @since 0.1.0
   */
  void Update(core::IWandererCore& core, visuals::Renderer& renderer);

  /**
   * Indicates whether or not the game should quit.
   *
   * @return true if the game should quit; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] inline bool ShouldQuit() const noexcept {
    return quit;
  }
};

}

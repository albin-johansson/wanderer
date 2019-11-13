#pragma once
#include "wanderer_core.h"
#include "renderer.h"
#include "key_state_manager.h"
#include <SDL_types.h>

namespace wanderer::controller {

/**
 * The FixedTimestepLoop class represents a fixed timestep game loop that uses delta time smoothing
 * and interpolation.
 *
 * @since 0.1.0
 */
class FixedTimestepLoop final {
 private:
  /**
   * A constant that denotes the maximum allowed frame time (delta time) in seconds. This is used
   * to avoid the "spiral of death" in the game loop.
   *
   * @since 0.1.0
   */
  static constexpr float MAX_FRAME_TIME = 0.25f;

  KeyStateManager_sptr keyStateManager = nullptr;
  Uint32 then = 0;
  Uint32 now = 0;
  const float vsyncDelta;
  float accumulator = 0;
  float delta = 0;
  float deltaBuffer = 0;
  bool quit = false;

  void UpdateInput(core::IWandererCore& core);

 public:
  /**
   * @param keyStateManager a shared pointer to the associated key state manager.
   * @param vsyncDelta the vsync delta time, in seconds.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  FixedTimestepLoop(KeyStateManager_sptr keyStateManager, float vsyncDelta);

  ~FixedTimestepLoop();

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

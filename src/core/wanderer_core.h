#pragma once
#include <memory>
#include "renderer.h"
#include "direction.h"
#include "input.h"
#include "viewport.h"

namespace wanderer::core {

/**
 * The IWandererCore interface specifies the facade of the core component of the Wanderer
 * application.
 *
 * @since 0.1.0
 */
class IWandererCore {
 protected:
  IWandererCore() = default;

 public:
  virtual ~IWandererCore() = default;

  /**
   * Handles the supplied input.
   *
   * @param input a reference to the input state object.
   * @since 0.1.0
   */
  virtual void HandleInput(const Input& input) = 0;

  /**
   * Updates the state of the core.
   *
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  virtual void Update(float delta) = 0;

  /**
   * Renders the components in the core model using interpolation.
   *
   * @param renderer a reference to the renderer that will be used.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  virtual void Render(visuals::Renderer& renderer, float alpha) = 0;

  virtual void Quit() noexcept = 0;

  /**
   * Sets the width of the viewport.
   *
   * @param width the new width of the viewport.
   * @since 0.1.0
   */
  virtual void SetViewportWidth(float width) = 0;

  /**
   * Sets the height of the viewport.
   *
   * @param height the new height of the viewport.
   * @since 0.1.0
   */
  virtual void SetViewportHeight(float height) = 0;

  /**
   * Moves the player entity.
   *
   * @param direction the direction in which the player will attempt to move.
   * @since 0.1.0
   */
  virtual void MovePlayer(Direction direction) = 0;

  /**
   * Stops the player entity from moving in the specified direction.
   *
   * @param direction the direction in which the player will stop moving in.
   * @since 0.1.0
   */
  virtual void StopPlayer(Direction direction) = 0;

  [[nodiscard]] virtual const Viewport& GetViewport() const noexcept = 0;

  [[nodiscard]] virtual bool ShouldQuit() const noexcept = 0;
};

using IWandererCore_uptr = std::unique_ptr<IWandererCore>;
using IWandererCore_sptr = std::shared_ptr<IWandererCore>;
using IWandererCore_wptr = std::weak_ptr<IWandererCore>;

}
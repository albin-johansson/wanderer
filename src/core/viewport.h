#pragma once
#include "rectangle.h"

namespace wanderer::core {

/**
 * The Viewport class represents the area that the user sees of the game world.
 *
 * @since 0.1.0
 */
class Viewport final {
 private:
  Rectangle bounds;
  float levelWidth;
  float levelHeight;

 public:
  /**
   * @param vpWidth the initial viewport width.
   * @param vpHeight the initial viewport height.
   * @param levelWidth the initial level width.
   * @param levelHeight the initial level height.
   * @since 0.1.0
   */
  Viewport(float vpWidth, float vpHeight, float levelWidth, float levelHeight) noexcept;

  /**
   * Tracks the viewport towards the object with the specified properties.
   *
   * @param tx the target x-coordinate.
   * @param ty the target y-coordinate.
   * @param w the width of the target.
   * @param h the height of the target.
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  void Track(float tx, float ty, float w, float h, float delta) noexcept;

  /**
   * Sets the width of the viewport.
   *
   * @param width the new width of the viewport.
   * @since 0.1.0
   */
  void SetWidth(float width) noexcept;

  /**
   * Sets the height of the viewport.
   *
   * @param height the new height of the viewport.
   * @since 0.1.0
   */
  void SetHeight(float height) noexcept;

  /**
   * Sets the width of the level.
   *
   * @param levelWidth the width of the level.
   * @since 0.1.0
   */
  void SetLevelWidth(float levelWidth) noexcept;

  /**
   * Sets the height of the level.
   *
   * @param levelHeight the height of the level.
   * @since 0.1.0
   */
  void SetLevelHeight(float levelHeight) noexcept;

  /**
   * Returns the current bounds of the viewport.
   *
   * @return the current bounds of the viewport.
   * @since 0.1.0
   */
  [[nodiscard]] inline Rectangle GetBounds() const noexcept { return bounds; }

  /**
   * Calculates and returns the translated value for the supplied x-coordinate.
   *
   * @param x the value that will be translated.
   * @return the translated value for the supplied x-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] inline float GetTranslatedX(float x) const noexcept {
    return x - bounds.GetX();
  }

  /**
   * Calculates and returns the translated value for the supplied y-coordinate.
   *
   * @param y the value that will be translated.
   * @return the translated value for the supplied y-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] inline float GetTranslatedY(float y) const noexcept {
    return y - bounds.GetY();
  }
};

}

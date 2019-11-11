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
  Viewport(int vpWidth, int vpHeight, int levelWidth, int levelHeight) noexcept;

  /**
   * Centers the viewport over the object with the specified properties.
   *
   * @param ox the x-coordinate of the object.
   * @param oy the y-coordinate of the object.
   * @param width the width of the object.
   * @param height the height of the object.
   * @since 0.1.0
   */
  void Center(float ox, float oy, int width, int height) noexcept;

  /**
   * Sets the width of the viewport.
   *
   * @param width the new width of the viewport.
   * @since 0.1.0
   */
  void SetWidth(int width) noexcept;

  /**
   * Sets the height of the viewport.
   *
   * @param height the new height of the viewport.
   * @since 0.1.0
   */
  void SetHeight(int height) noexcept;

  /**
   * Sets the width of the level.
   *
   * @param levelWidth the width of the level.
   * @since 0.1.0
   */
  void SetLevelWidth(int levelWidth) noexcept;

  /**
   * Sets the height of the level.
   *
   * @param levelHeight the height of the level.
   * @since 0.1.0
   */
  void SetLevelHeight(int levelHeight) noexcept;

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

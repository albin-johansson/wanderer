#pragma once
#include <renderer.h>
#include <sound_id.h>

#include <memory>
#include <string>

#include "wanderer_stdinc.h"

namespace wanderer {

class IPlayer;
class ITileMap;
class Input;

/**
 * The IWandererCore interface specifies the facade of the core component of the
 * Wanderer application.
 *
 * @since 0.1.0
 */
class IWandererCore {  // TODO remove
 public:
  virtual ~IWandererCore() = default;

  /**
   * Handles the supplied input.
   *
   * @param input a reference to the input state object.
   * @since 0.1.0
   */
  virtual void handle_input(const Input& input) = 0;

  /**
   * Updates the state of the core.
   *
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  virtual void update(float delta) = 0;

  /**
   * Renders the components in the core model using interpolation.
   *
   * @param renderer a reference to the renderer that will be used.
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  virtual void render(ctn::Renderer& renderer, float alpha) = 0;

  /**
   * Sets the currently active map.
   *
   * @param map the map that should be made active.
   * @since 0.1.0
   */
  virtual void set_map(SharedPtr<ITileMap> map) = 0;

  /**
   * Plays a sound.
   *
   * @param id the ID of the sound that will be played.
   * @since 0.1.0
   */
  virtual void play_sound(SoundID id) const = 0;

  /**
   * Enables the hint that the game should quit as soon as possible.
   *
   * @since 0.1.0
   */
  virtual void quit() noexcept = 0;

  /**
   * Sets the width of the viewport.
   *
   * @param width the new width of the viewport.
   * @since 0.1.0
   */
  virtual void set_viewport_width(float width) = 0;

  /**
   * Sets the height of the viewport.
   *
   * @param height the new height of the viewport.
   * @since 0.1.0
   */
  virtual void set_viewport_height(float height) = 0;

  /**
   * Indicates whether or not the game should quit.
   *
   * @return true if the game should quit; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] virtual bool should_quit() const noexcept = 0;

  /**
   * Returns a reference to the player.
   *
   * @return a reference to the player.
   * @since 0.1.0
   */
  [[nodiscard]] virtual const IPlayer& get_player() const = 0;

  /**
   * Returns the currently active map.
   *
   * @return the currently active map.
   * @since 0.1.0
   */
  [[nodiscard]] virtual const ITileMap& get_active_map() const = 0;

  // TODO add method for changing active menu
};

}  // namespace wanderer
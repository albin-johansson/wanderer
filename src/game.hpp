#pragma once

#include <cen/key_state.hpp>
#include <cen/mouse_state.hpp>
#include <cen/renderer.hpp>

#include "alpha.hpp"
#include "delta.hpp"
#include "level.hpp"
#include "level_manager.hpp"
#include "menu_manager.hpp"
#include "texture_cache.hpp"

namespace wanderer {

/**
 * \class game
 *
 * \brief Represents the Wanderer game.
 *
 * \details This class is responsible for managing the game state and
 * updating the systems. This class is the core of the entire game.
 *
 * \headerfile game.hpp
 */
class game final
{
 public:
  /**
   * \brief Creates a `game` instance.
   *
   * \param renderer the renderer used to create the initial textures.
   */
  explicit game(cen::renderer& renderer);

  ~game() noexcept;

  /**
   * \brief Responds to user input.
   *
   * \param mouseState the current mouse input state.
   * \param keyState the current keyboard input state.
   */
  void handle_input(const cen::mouse_state& mouseState,
                    const cen::key_state& keyState);

  /**
   * \brief Updates the state of the game.
   *
   * \param dt the delta time, in seconds.
   */
  void tick(delta dt);

  /**
   * \brief Renders the game.
   *
   * \param renderer the renderer used to render the game.
   */
  void render(cen::renderer& renderer);

  /**
   * \brief Indicates whether or not the game should quit.
   *
   * \return `true` if the game should quit; `false` otherwise.
   */
  [[nodiscard]] auto quit_requested() const noexcept -> bool
  {
    return m_menus.quit_requested();
  }

 private:
  entt::dispatcher m_dispatcher;
  texture_cache m_imageCache;
  level_manager m_levels;
  menu_manager m_menus;
};

}  // namespace wanderer

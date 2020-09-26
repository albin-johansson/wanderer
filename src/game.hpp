#pragma once

#include <cen/key_state.hpp>
#include <cen/mouse_state.hpp>
#include <cen/renderer.hpp>

#include "aabb_tree.hpp"
#include "alpha.hpp"
#include "component/tilemap.hpp"
#include "component/viewport.hpp"
#include "delta.hpp"
#include "image_cache.hpp"
#include "level.hpp"

namespace wanderer {

/**
 * @class game
 *
 * @brief Represents the Wanderer game.
 *
 * @details This class is responsible for managing the game state and
 * updating the systems. This class is the core of the entire game.
 *
 * @headerfile game.hpp
 */
class game final
{
 public:
  /**
   * @brief Creates a `game` instance.
   *
   * @param renderer the renderer used to create the initial textures.
   */
  explicit game(cen::renderer& renderer);

  ~game() noexcept;

  /**
   * @brief Responds to user input.
   *
   * @param mouseState the current mouse input state.
   * @param keyState the current keyboard input state.
   */
  void handle_input(const cen::mouse_state& mouseState,
                    const cen::key_state& keyState);

  /**
   * @brief Updates the state of the game.
   *
   * @param dt the delta time, in seconds.
   */
  void tick(delta dt);

  /**
   * @brief Renders the game.
   *
   * @param renderer the renderer used to render the game.
   */
  void render(cen::renderer& renderer);

 private:
  level m_level{};
  entt::dispatcher m_dispatcher;
  image_cache m_imageCache;
  comp::tilemap::entity m_world{null<comp::tilemap>()};
  entt::entity m_player;
  comp::viewport::entity m_viewport{null<comp::viewport>()};
};

}  // namespace wanderer

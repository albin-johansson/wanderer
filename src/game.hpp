#pragma once

#include <renderer.hpp>

#include "component/tilemap.hpp"
#include "component/viewport.hpp"
#include "image_cache.hpp"
#include "input.hpp"
#include "wanderer_stdinc.hpp"

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
   * @param input the current state of the key and mouse input.
   */
  void handle_input(const Input& input);

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
   * @param alpha the interpolation coefficient, in the range [0, 1].
   */
  void render(cen::renderer& renderer, alpha alpha);

 private:
  entt::registry m_registry;  // TODO consider multiple registries
  entt::dispatcher m_dispatcher;
  image_cache m_imageCache;
  comp::tilemap::entity m_world{null<comp::tilemap>()};
  entt::entity m_player;
  comp::viewport::entity m_viewport{null<comp::viewport>()};
};

}  // namespace wanderer

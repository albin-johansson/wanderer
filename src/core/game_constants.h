#pragma once

namespace albinjohansson::wanderer {

/**
 * The GameConstants struct holds various important game constants.
 *
 * @since 0.1.0
 */
struct GameConstants final {
  /**
   * The logical width of the game.
   *
   * @since 0.1.0
   */
  static constexpr int logical_width = 1280;

  /**
   * The logical height of the game.
   *
   * @since 0.1.0
   */
  static constexpr int logical_height = 720;

  /**
   * The size (width and height) of all tiles in the game.
   *
   * @since 0.1.0
   */
  static constexpr float tile_size = 64;

  static constexpr float entity_width = 150;
  static constexpr float entity_height = 150;

  /**
   * The logical size (width and height) of all tiles. This constant is the same as tile_size,
   * represented as an integer.
   *
   * @since 0.1.0
   */
  static constexpr int tile_size_int = static_cast<int>(tile_size);

  /**
   * The speed of the player.
   *
   * @since 0.1.0
   */
  static constexpr float player_speed = 230;

  /**
   * The speed of mobs.
   *
   * @since 0.1.0
   */
  static constexpr float mob_speed = 200;

  /**
   * The maximum health of the player.
   *
   * @since 0.1.0
   */
  static constexpr int player_max_health = 100;

  GameConstants() = delete;

  ~GameConstants() = default;
};

}

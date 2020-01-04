#pragma once

/**
 * This file holds various important game constants.
 *
 * @since 0.1.0
 */

namespace albinjohansson::wanderer {

// 1280x720, 1366x768, 1600x900

/**
 * The logical width of the game.
 *
 * @since 0.1.0
 */
constexpr int GAME_LOGICAL_WIDTH = 1280;

/**
 * The logical height of the game.
 *
 * @since 0.1.0
 */
constexpr int GAME_LOGICAL_HEIGHT = 720;

/**
 * The size (width and height) of all tiles in the game.
 *
 * @since 0.1.0
 */
constexpr float TILE_SIZE = 64;

/**
 * The logical size (width and height) of all tiles. This constant is the same as TILE_SIZE,
 * represented as an integer.
 *
 * @since 0.1.0
 */
constexpr int TILE_SIZE_INT = 64;

/**
 * The speed of the player.
 *
 * @since 0.1.0
 */
constexpr float PLAYER_SPEED = 230;

/**
 * The speed of mobs.
 *
 * @since 0.1.0
 */
constexpr float MOB_SPEED = 200;

/**
 * The maximum health of the player.
 *
 * @since 0.1.0
 */
constexpr int PLAYER_MAX_HEALTH = 100;

}

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
constexpr int gameLogicalWidth = 1280;

/**
 * The logical height of the game.
 *
 * @since 0.1.0
 */
constexpr int gameLogicalHeight = 720;

/**
 * The size (width and height) of all tiles in the game.
 *
 * @since 0.1.0
 */
constexpr float tileSize = 64;

/**
 * The logical size (width and height) of all tiles. This constant is the same as TILE_SIZE,
 * represented as an integer.
 *
 * @since 0.1.0
 */
constexpr int tileSizeInt = 64;

/**
 * The speed of the player.
 *
 * @since 0.1.0
 */
constexpr float playerSpeed = 230;

/**
 * The speed of mobs.
 *
 * @since 0.1.0
 */
constexpr float mobSpeed = 200;

/**
 * The maximum health of the player.
 *
 * @since 0.1.0
 */
constexpr int playerMaxHealth = 100;

}

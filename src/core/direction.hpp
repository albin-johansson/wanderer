/**
 * @brief Provides the `Direction` enum class.
 * @file direction.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

namespace wanderer {

/**
 * @enum Direction
 * @brief Represents four different directions.
 *
 * @var Direction::Up
 * Represents the direction "up", or north.
 * @var Direction::Right
 * Represents the direction "right", or east.
 * @var Direction::Down
 * Represents the direction "down", or south.
 * @var Direction::Left
 * Represents the direction "left", or west.
 *
 * @headerfile direction.hpp
 */
enum class Direction { Up, Right, Down, Left };

}  // namespace wanderer

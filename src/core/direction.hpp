#pragma once

namespace wanderer {

/**
 * \enum direction
 *
 * \brief Represents four different directions.
 *
 * \var direction::up
 * Represents the direction "up", or north.
 * \var direction::right
 * Represents the direction "right", or east.
 * \var direction::down
 * Represents the direction "down", or south.
 * \var direction::left
 * Represents the direction "left", or west.
 *
 * \headerfile direction.hpp
 */
enum class direction
{
  up,
  right,
  down,
  left
};

}  // namespace wanderer

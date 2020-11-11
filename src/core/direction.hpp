#pragma once

namespace wanderer {

/**
 * \enum direction
 *
 * \brief Represents four different directions.
 *
 * \headerfile direction.hpp
 */
enum class direction
{
  up,     ///< Represents the direction "up", or north.
  right,  ///< Represents the direction "right", or east.
  down,   ///< Represents the direction "down", or south.
  left    ///< Represents the direction "left", or west.
};

}  // namespace wanderer

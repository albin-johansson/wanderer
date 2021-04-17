#pragma once

namespace wanderer {

/**
 * \brief Simply represents a row/column pair.
 *
 * \ingroup core
 */
struct grid_position final
{
  float row{};  ///< The row index.
  float col{};  ///< The column index.
};

}  // namespace wanderer

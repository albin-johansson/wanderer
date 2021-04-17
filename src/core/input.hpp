#pragma once

#include <centurion.hpp>  // keyboard, mouse

namespace wanderer {

/// \brief A simple wrapper around the keyboard and mouse state
/// \ingroup core
struct input final
{
  cen::keyboard keyboard;  ///< The keyboard state.
  cen::mouse mouse;        ///< The mouse state.
};

}  // namespace wanderer

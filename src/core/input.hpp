#pragma once

#include <centurion.hpp>  // keyboard, mouse

namespace wanderer {

/// A simple wrapper around the keyboard and mouse state
struct input final
{
  cen::keyboard keyboard;  ///< The keyboard state.
  cen::mouse mouse;        ///< The mouse state.
};

}  // namespace wanderer

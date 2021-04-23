#pragma once

#include <centurion.hpp>  // surface

namespace wanderer::ctx {

/**
 * \brief Contains a snapshot of the rendering target, used for save file previews.
 *
 * \ingroup ctx
 */
struct renderer_snapshot final
{
  cen::surface surface;  ///< The snapshot of the rendering target.
};

}  // namespace wanderer::ctx

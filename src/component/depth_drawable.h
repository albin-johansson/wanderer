/**
 * Provides the declaration of the <code>DepthDrawable</code> component.
 *
 * @file depth_drawable.h
 */

#pragma once

#include <area.h>
#include <rect.h>
#include <texture.h>

#include <entt.hpp>

#include "wanderer_stdinc.h"

namespace wanderer {  // TODO wanderer::component namespace

/**
 * The DepthDrawable component holds data required to be able to render
 * entities in such a way that the drawables are arranged in relation to their
 * depth heuristic and Y-coordinate of their center points.
 */
struct DepthDrawable final {
  entt::handle<ctn::Texture> texture;  // handle to associated texture
  Depth depth{5};    // heuristic used to determine render order
  float centerY{0};  // current center point y-coordinate
  ctn::IRect src{};  // source cutout used when rendering
  ctn::FRect dst{};  // destination and size of the rendered texture
};

}  // namespace wanderer

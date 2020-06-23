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

namespace wanderer {  // TODO wanderer::component namespace

/**
 * The DepthDrawable component holds data required to be able to render
 * entities in such a way that the drawables are arranged in relation to their
 * depth heuristic and Y-coordinate of their center points.
 */
struct DepthDrawable final {
  entt::handle<centurion::Texture> texture;  // handle to associated texture
  Depth depth{5};           // heuristic used to determine render order
  float centerY{0};         // current center point y-coordinate
  centurion::IRect src{};   // source cutout used when rendering
  centurion::FArea size{};  // actual size of the rendered texture
};

}  // namespace wanderer

#pragma once

#include "core/aliases/float2.hpp"

namespace wanderer::comp {

/**
 * \struct point_light
 *
 * \brief Represents a light source.
 *
 * \ingroup components
 */
struct point_light final
{
  float2 position;      ///< The world position of the light.
  float size{};         ///< Base size of the light.
  float fluctuation{};  ///< Fluctuation size in [-fluctuationLimit, fluctuationLimit].
  float fluctuationStep{};   ///< Size of each fluctuation increment.
  float fluctuationLimit{};  ///< Fluctuation size limit.
};

void serialize(auto& archive, point_light& pl)
{
  archive(pl.position, pl.size, pl.fluctuation, pl.fluctuationStep, pl.fluctuationLimit);
}

}  // namespace wanderer::comp

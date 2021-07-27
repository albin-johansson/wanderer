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
  float fluctuation_step{};   ///< Size of each fluctuation increment.
  float fluctuation_limit{};  ///< Fluctuation size limit.
};

void serialize(auto& archive, point_light& pl)
{
  archive(pl.position,
          pl.size,
          pl.fluctuation,
          pl.fluctuation_step,
          pl.fluctuation_limit);
}

}  // namespace wanderer::comp

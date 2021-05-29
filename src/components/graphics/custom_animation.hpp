#pragma once

#include <string_view>  // string_view

namespace wanderer::comp {

struct custom_animation final
{
  std::string_view msg;  ///< Optional message used to assign meaning to the animation.
  float speed{};         ///< Speed scale factor.
  float width{};         ///< Current width of the left and right "bars".
  float height{};        ///< Current height of the top- and bottom "bars".
  float x_step_size{};   ///< Size of an animation step in the x-axis.
  float y_step_size{};   ///< Size of an animation step in the y-axis.
  bool fading_in{};      ///< Indicates whether or not the animation is "fading" inwards.
};

}  // namespace wanderer::comp

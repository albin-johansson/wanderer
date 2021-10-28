#ifndef RUNE_CONFIGURATION_HPP_
#define RUNE_CONFIGURATION_HPP_

#include <centurion.hpp>  // window, renderer, iarea
#include <cstdint>        // uint32_t
#include <string>         // string

namespace rune {

/// \addtogroup core
/// \{

struct configuration final
{
  std::string window_title{"Rune"};
  cen::iarea window_size{cen::window::default_size()};
  std::uint32_t renderer_flags{cen::renderer::default_flags()};
  double max_tick_rate{120.0};
  int max_frames_per_tick{5};
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CONFIGURATION_HPP_

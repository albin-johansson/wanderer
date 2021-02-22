#include "files_directory.hpp"

#include <cen/pref_path.hpp>

namespace wanderer {

auto files_directory() -> const std::string&
{
  static auto path = cen::get_pref_path("albin-johansson", "wanderer").copy();
  return path;
}

}  // namespace wanderer

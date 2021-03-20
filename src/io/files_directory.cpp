#include "files_directory.hpp"

#include <centurion.hpp>

namespace wanderer {

auto files_directory() -> const std::filesystem::path&
{
  static std::filesystem::path path =
      cen::get_pref_path("albin-johansson", "wanderer").copy();
  return path;
}

}  // namespace wanderer

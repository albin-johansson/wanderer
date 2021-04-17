#include "files_directory.hpp"

#include <centurion.hpp>  // preferred_path

namespace wanderer {

auto files_directory() -> const std::filesystem::path&
{
  static std::filesystem::path path =
      cen::preferred_path("albin-johansson", "wanderer").copy();
  return path;
}

}  // namespace wanderer

#include "directories.hpp"

#include <centurion.hpp>

namespace wanderer {

auto get_persistent_file_dir() -> const std::filesystem::path&
{
  static const std::filesystem::path path =
      cen::preferred_path("albin-johansson", "wanderer").copy();
  return path;
}

auto get_saves_dir() -> const std::filesystem::path&
{
  static const auto path = get_persistent_file_dir() / "saves";
  return path;
}

}  // namespace wanderer

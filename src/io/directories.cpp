#include "directories.hpp"

#include <centurion.hpp>  // preferred_path

namespace wanderer {

auto GetFilesDirectory() -> const std::filesystem::path&
{
  static const std::filesystem::path path =
      cen::preferred_path("albin-johansson", "wanderer").copy();
  return path;
}

auto GetSavesDirectory() -> const std::filesystem::path&
{
  static const auto path = GetFilesDirectory() / "saves";
  return path;
}

}  // namespace wanderer

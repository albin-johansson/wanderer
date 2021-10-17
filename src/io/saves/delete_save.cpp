#include "delete_save.hpp"

#include <filesystem>  // remove_all

#include "io/directories.hpp"

namespace wanderer {

void delete_save(const std::string& name)
{
  const auto dir = GetSavesDirectory() / name;
  std::filesystem::remove_all(dir);
}

}  // namespace wanderer

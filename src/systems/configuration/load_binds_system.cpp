#include "load_binds_system.hpp"

#include <filesystem>  // exists, copy, path
#include <fstream>     // ifstream

#include "io/files_directory.hpp"
#include "io/ini.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto parse_binds(const std::filesystem::path& path) -> ctx::binds
{
  CENTURION_LOG_INFO("Reading binds: \"%s\"", path.string().c_str());

  std::ifstream stream{path};
  const ini_file file{stream};

  ctx::binds binds;

  binds.up = file.get<std::string>("Input", "MoveUp").value_or("W");
  binds.down = file.get<std::string>("Input", "MoveDown").value_or("S");
  binds.right = file.get<std::string>("Input", "MoveRight").value_or("D");
  binds.left = file.get<std::string>("Input", "MoveLeft").value_or("A");
  binds.attack = file.get<std::string>("Input", "Attack").value_or("Space");
  binds.interact = file.get<std::string>("Input", "Interact").value_or("E");
  binds.inventory = file.get<std::string>("Input", "Inventory").value_or("I");

  return binds;
}

}  // namespace

auto load_binds() -> ctx::binds
{
  static const auto path = files_directory() / "binds.ini";
  if (std::filesystem::exists(path))
  {
    return parse_binds(path);
  }
  else
  {
    std::filesystem::copy("resources/binds.ini", path);
    return ctx::binds{};
  }
}

}  // namespace wanderer::sys

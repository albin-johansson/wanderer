#include "load_binds_system.hpp"

#include <filesystem>  // exists, copy, path
#include <rune.hpp>    // ini_file

#include "io/directories.hpp"

namespace wanderer::sys {
namespace {

inline const auto binds_file = files_directory() / "binds.ini";

[[nodiscard]] auto parse_binds() -> ctx::binds
{
  CENTURION_LOG_INFO("Reading binds: \"%s\"", binds_file.string().c_str());
  ctx::binds binds;

  const auto ini = rune::read_ini(binds_file);

  const auto& input = ini.at("Input");
  binds.up = input.at("MoveUp").get<std::string>();
  binds.down = input.at("MoveDown").get<std::string>();
  binds.right = input.at("MoveRight").get<std::string>();
  binds.left = input.at("MoveLeft").get<std::string>();
  binds.attack = input.at("Attack").get<std::string>();
  binds.interact = input.at("Interact").get<std::string>();
  binds.inventory = input.at("Inventory").get<std::string>();

  return binds;
}

}  // namespace

auto load_binds() -> ctx::binds
{
  if (std::filesystem::exists(binds_file))
  {
    return parse_binds();
  }
  else
  {
    std::filesystem::copy("resources/binds.ini", binds_file);
    return ctx::binds{};
  }
}

}  // namespace wanderer::sys

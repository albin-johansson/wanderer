#include "load_binds_system.hpp"

#include <filesystem>           // exists, copy, path
#include <rune/everything.hpp>  // ini_file

#include "io/directories.hpp"

namespace wanderer::sys {
namespace {

inline const auto binds_file = GetFilesDirectory() / "binds.ini";

[[nodiscard]] auto ParseBinds() -> ctx::Binds
{
  CENTURION_LOG_INFO("Reading binds: \"%s\"", binds_file.string().c_str());
  ctx::Binds binds;

  const auto ini = rune::read_ini(binds_file).value();

  const auto& input = ini.at("Input");
  binds.up = input.at("MoveUp").as<std::string>();
  binds.down = input.at("MoveDown").as<std::string>();
  binds.right = input.at("MoveRight").as<std::string>();
  binds.left = input.at("MoveLeft").as<std::string>();
  binds.attack = input.at("Attack").as<std::string>();
  binds.interact = input.at("Interact").as<std::string>();
  binds.inventory = input.at("Inventory").as<std::string>();

  return binds;
}

}  // namespace

auto LoadBinds() -> ctx::Binds
{
  if (std::filesystem::exists(binds_file)) {
    return ParseBinds();
  }
  else {
    std::filesystem::copy("resources/binds.ini", binds_file);
    return ctx::Binds{};
  }
}

}  // namespace wanderer::sys

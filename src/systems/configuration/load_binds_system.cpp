#include "load_binds_system.hpp"

#include <filesystem>           // exists, copy, path
#include <rune/everything.hpp>  // ini_file

#include "io/directories.hpp"

namespace wanderer::sys {
namespace {

inline const auto binds_file = files_directory() / "binds.ini";

[[nodiscard]] auto parse_binds() -> ctx::binds
{
  CENTURION_LOG_INFO("Reading binds: \"%s\"", binds_file.string().c_str());
  ctx::binds binds;

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

auto load_binds() -> ctx::binds
{
  if (std::filesystem::exists(binds_file)) {
    return parse_binds();
  }
  else {
    std::filesystem::copy("resources/binds.ini", binds_file);
    return ctx::binds{};
  }
}

}  // namespace wanderer::sys

#include "load_binds_system.hpp"

#include <filesystem>  // exists, copy
#include <fstream>     // ifstream

#include "files_directory.hpp"
#include "ini.hpp"

namespace wanderer::sys {

auto load_binds() -> ctx::binds
{
  ctx::binds binds;

  try
  {
    const auto path = files_directory() / "binds.ini";
    if (std::filesystem::exists(path))
    {
      CENTURION_LOG_INFO("Reading binds: \"%s\"", path.string().c_str());

      std::ifstream stream{path};
      const ini_file file{stream};

      binds.up = file.get<std::string>("Input", "MoveUp").value_or("W");
      binds.down = file.get<std::string>("Input", "MoveDown").value_or("S");
      binds.right = file.get<std::string>("Input", "MoveRight").value_or("D");
      binds.left = file.get<std::string>("Input", "MoveLeft").value_or("A");

      binds.attack = file.get<std::string>("Input", "Attack").value_or("Space");
      binds.interact = file.get<std::string>("Input", "Interact").value_or("E");
      binds.inventory = file.get<std::string>("Input", "Inventory").value_or("I");
    }
    else
    {
      std::filesystem::copy("resources/binds.ini", path);
    }
  } catch (...)
  {
    cen::log::error("Failed to load binds!");
  }

  return binds;
}

}  // namespace wanderer::sys

#include "parse_menu.hpp"

#include <centurion.hpp>
#include <fstream>   // ifstream
#include <json.hpp>  // json
#include <memory>    // unique_ptr
#include <string>    // string
#include <vector>    // vector

#include "action.hpp"
#include "button.hpp"
#include "menu_action.hpp"
#include "quit_action.hpp"
#include "switch_menu_action.hpp"

using nlohmann::json;

namespace wanderer {
namespace {

[[nodiscard]] auto create_action(const menu_action menuAction)
    -> std::unique_ptr<action>
{
  switch (menuAction)
  {
    case menu_action::quit:
      return std::make_unique<quit_action>();

    case menu_action::goto_in_game:
      return std::make_unique<switch_menu_action>(menu_id::in_game);

    case menu_action::goto_home:
      return std::make_unique<switch_menu_action>(menu_id::home);

    case menu_action::goto_settings:
      return std::make_unique<switch_menu_action>(menu_id::settings);

    case menu_action::goto_saves:
      return std::make_unique<switch_menu_action>(menu_id::saves);

    case menu_action::goto_controls:
      return std::make_unique<switch_menu_action>(menu_id::controls);

    default:
      cen::log::warn("Failed to create action from menu action: %i",
                     menuAction);
      return nullptr;
  }
}

[[nodiscard]] auto parse_button(entt::registry& registry, const json& json)
    -> comp::button::entity
{
  const auto entity = registry.create();

  auto& button = registry.emplace<comp::button>(entity);
  button.action = create_action(json.at("action").get<menu_action>());
  button.text = json.at("text").get<std::string>();
  button.row = json.at("row").get<int>();
  button.col = json.at("col").get<int>();

  registry.emplace<comp::button_drawable>(entity);

  return comp::button::entity{entity};
}

[[nodiscard]] auto parse_buttons(entt::registry& registry, const json& json)
    -> std::vector<comp::button::entity>
{
  std::vector<comp::button::entity> buttons;

  const auto& buttonsJson = json.at("buttons");
  buttons.reserve(buttonsJson.size());

  for (const auto& [key, value] : buttonsJson.items())
  {
    buttons.emplace_back(parse_button(registry, value));
  }

  return buttons;
}

[[nodiscard]] auto parse_bind(entt::registry& registry, const json& json)
    -> comp::key_bind::entity
{
  const auto entity = registry.create();
  auto& bind = registry.emplace<comp::key_bind>(entity);

  const auto keyName = json.at("key").get<std::string>();
  bind.key = cen::scan_code{keyName.c_str()};
  bind.action = create_action(json.at("action").get<menu_action>());

  return comp::key_bind::entity{entity};
}

[[nodiscard]] auto parse_binds(entt::registry& registry, const json& json)
    -> std::vector<comp::key_bind::entity>
{
  std::vector<comp::key_bind::entity> binds;

  const auto& bindsJson = json.at("binds");
  binds.reserve(bindsJson.size());

  for (const auto& [key, value] : bindsJson.items())
  {
    binds.emplace_back(parse_bind(registry, value));
  }

  return binds;
}

}  // namespace

auto parse_menu(entt::registry& registry, const std::filesystem::path& path)
    -> comp::menu::entity
{
  json json;

  std::ifstream stream{path};
  stream >> json;

  const auto entity = registry.create();

  auto& menu = registry.emplace<comp::menu>(entity);
  menu.id = json.at("id").get<menu_id>();
  menu.title = json.at("title").get<std::string>();
  menu.blocking = json.at("isBlocking").get<bool>();

  auto& bindsPack = registry.emplace<comp::key_bind_pack>(entity);
  bindsPack.binds = parse_binds(registry, json);

  auto& buttonPack = registry.emplace<comp::button_pack>(entity);
  buttonPack.buttons = parse_buttons(registry, json);

  registry.emplace<comp::menu_drawable>(entity);

  return comp::menu::entity{entity};
}

}  // namespace wanderer

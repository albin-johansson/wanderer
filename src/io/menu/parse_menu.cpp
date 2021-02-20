#include "parse_menu.hpp"

#include <fstream>   // ifstream
#include <json.hpp>  // json
#include <string>    // string
#include <utility>   // move
#include <vector>    // vector

#include "menu_button.hpp"

using nlohmann::json;

namespace wanderer {
namespace {

[[nodiscard]] auto parse_button(const json& json) -> menu_button
{
  auto text = json.at("text").get<std::string>();
  const auto action = json.at("action").get<menu_action>();
  const auto row = json.at("row").get<int>();
  const auto col = json.at("col").get<int>();
  return menu_button{action, std::move(text), row, col};
}

[[nodiscard]] auto parse_buttons(const json& json) -> std::vector<menu_button>
{
  std::vector<menu_button> buttons;

  const auto& buttonsJson = json.at("buttons");
  buttons.reserve(buttonsJson.size());

  for (const auto& [key, value] : buttonsJson.items()) {
    buttons.emplace_back(parse_button(value));
  }

  return buttons;
}

[[nodiscard]] auto parse_bind(const json& json) -> key_bind
{
  key_bind bind;

  const auto keyName = json.at("key").get<std::string>();
  bind.key = cen::scan_code{keyName.c_str()};

  json.at("action").get_to(bind.action);

  return bind;
}

[[nodiscard]] auto parse_binds(const json& json) -> std::vector<key_bind>
{
  std::vector<key_bind> binds;

  const auto& bindsJson = json.at("binds");
  binds.reserve(bindsJson.size());

  for (const auto& [key, value] : bindsJson.items()) {
    binds.emplace_back(parse_bind(value));
  }

  return binds;
}

}  // namespace

auto parse_menu(const std::filesystem::path& path) -> comp::menu
{
  json json;

  std::ifstream stream{path};
  stream >> json;

  comp::menu m;
  m.id = json.at("id").get<menu_id>();
  m.title = json.at("title").get<std::string>();
  m.blocking = json.at("isBlocking").get<bool>();
  m.buttons = parse_buttons(json);
  m.binds = parse_binds(json);

  return m;
}

}  // namespace wanderer

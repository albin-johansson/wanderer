#include "make_menu.hpp"

#include <fstream>  // ifstream
#include <json.hpp>

#include "menu_button.hpp"

using nlohmann::json;
using std::filesystem::path;

namespace wanderer {
namespace {

[[nodiscard]] auto make_button(const json& json) -> menu_button
{
  auto text = json.at("text").get<std::string>();
  const auto action = json.at("action").get<menu_action>();

  menu_button button{action, std::move(text)};

  const auto x = json.at("x").get<float>();
  const auto y = json.at("y").get<float>();
  const auto width = json.at("width").get<float>();
  const auto height = json.at("height").get<float>();

  button.set_bounds({{x, y}, {width, height}});

  return button;
}

[[nodiscard]] auto make_buttons(const json& json) -> std::vector<menu_button>
{
  std::vector<menu_button> buttons;

  const auto& buttonsJson = json.at("buttons");
  buttons.reserve(buttonsJson.size());

  for (const auto& [key, value] : buttonsJson.items()) {
    buttons.emplace_back(make_button(value));
  }

  return buttons;
}

[[nodiscard]] auto make_bind(const json& json) -> key_bind
{
  key_bind bind;

  const auto keyName = json.at("key").get<std::string>();
  bind.key = cen::scan_code{keyName.c_str()};

  json.at("action").get_to(bind.action);

  return bind;
}

[[nodiscard]] auto make_binds(const json& json) -> std::vector<key_bind>
{
  std::vector<key_bind> binds;

  const auto& bindsJson = json.at("binds");
  binds.reserve(bindsJson.size());

  for (const auto& [key, value] : bindsJson.items()) {
    binds.emplace_back(make_bind(value));
  }

  return binds;
}

}  // namespace

auto make_menu(const path& path) -> menu
{
  json json;

  std::ifstream stream{path};
  stream >> json;

  menu m;
  m.m_title = json.at("title").get<std::string>();
  m.m_blocking = json.at("isBlocking").get<bool>();
  m.m_buttons = make_buttons(json);
  m.m_binds = make_binds(json);

  return m;
}

}  // namespace wanderer

#include "menu_builder.h"

#include <fstream>

#include "key_bind.h"
#include "menu_button.h"
#include "menu_impl.h"

using namespace centurion;

namespace albinjohansson::wanderer {
namespace {

UniquePtr<MenuButton> create_button(ActionParser& actionParser,
                                    const JsonValue& value,
                                    int row)
{
  const auto text = value.at("text").get<std::string>();

  auto action = actionParser.parse(value.at("action"));
  const auto x = 200.0f;
  const auto y = 200.0f + static_cast<float>(row * 70);

  return std::make_unique<MenuButton>(
      text, FRect{x, y, 200, 50}, std::move(action));
}

UniquePtr<KeyBind> create_key_bind(ActionParser& actionParser,
                                   const JsonValue& value)
{
  const auto keyStr = value.at("key").get<std::string>();
  const auto actionStr = value.at("action").get<std::string>();

  auto action = actionParser.parse(value.at("action"));
  if (!action) {
    Log::warn("Failed to load bind action: %s",
              value.at("key").get<std::string>().c_str());
    return nullptr;
  }

  if (!value.count("trigger")) {
    Log::warn("Key bind must have \"trigger\" key! Ignoring bind...");
    return nullptr;
  }

  auto trigger = value.at("trigger").get<KeyBind::Trigger>();

  Key key = SDL_GetKeyFromName(keyStr.c_str());
  if (key.scancode() == SDL_SCANCODE_UNKNOWN) {
    Log::warn("Didn't recognize the key \"%s\"!", keyStr.c_str());
    return nullptr;
  }

  return std::make_unique<KeyBind>(std::move(action), key, trigger);
}

}  // namespace

UniquePtr<IMenu> MenuBuilder::build(ActionParser& actionParser, CZString file)
{
  std::ifstream stream{file};
  Json json;

  stream >> json;

  auto* m = new MenuImpl{};
  auto menu = std::unique_ptr<MenuImpl>(m);

  try {
    menu->m_title = json.at("title").get<std::string>();
  } catch (...) {
    Log::critical("Menu didn't have \"title\" key!");
    throw;
  }

  try {
    menu->m_blocking = json.at("isBlocking").get<bool>();
  } catch (...) {
    Log::critical("Menu didn't have \"isBlocking\" key!");
    throw;
  }

  int row = 0;
  if (json.count("buttons")) {
    for (const auto& [key, value] : json.at("buttons").items()) {
      auto button = create_button(actionParser, value, row);
      if (button) {
        menu->m_buttons.push_back(std::move(button));
        ++row;
      }
    }
  } else {
    Log::warn("Menu \"%s\" doesn't feature \"buttons\" key!",
              menu->m_title.c_str());
  }

  if (json.count("binds")) {
    for (const auto& [key, value] : json.at("binds").items()) {
      auto bind = create_key_bind(actionParser, value);
      if (bind) {
        menu->m_binds.push_back(std::move(bind));
      }
    }
  } else {
    Log::warn("Menu \"%s\" doesn't feature \"binds\" key!",
              menu->m_title.c_str());
  }

  return menu;
}

}  // namespace albinjohansson::wanderer

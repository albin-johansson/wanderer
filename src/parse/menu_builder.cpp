#include "menu_builder.h"

#include <fstream>

#include "json_utils.h"
#include "key_bind.h"
#include "key_bind_parser.h"
#include "menu_button_parser.h"
#include "menu_impl.h"
#include "wanderer_exception.h"

using namespace centurion;

namespace albinjohansson::wanderer {

UniquePtr<IMenu> MenuParser::parse(ActionParser& actionParser, CZString file)
{
  Json json = parse_json(file);

  auto menu = std::unique_ptr<MenuImpl>(new MenuImpl{});

  if (const auto title = maybe_get<std::string>(json, "title"); title) {
    menu->m_title = std::move(*title);
  } else {
    throw WandererException{"Menu didn't have \"title\" attribute!"};
  }

  if (const auto isBlocking = maybe_get<bool>(json, "isBlocking"); isBlocking) {
    menu->m_blocking = *isBlocking;
  } else {
    throw WandererException{"Menu didn't have \"isBlocking\" attribute!"};
  }

  int row = 0;
  if (json.count("buttons")) {
    for (const auto& [key, value] : json.at("buttons").items()) {
      auto button = MenuButtonParser::parse(actionParser, value, row);
      if (button) {
        menu->m_buttons.push_back(std::move(button));
        ++row;
      }
    }
  } else {
    Log::warn("Menu \"%s\" doesn't feature \"buttons\" attribute!",
              menu->m_title.c_str());
  }

  if (json.count("binds")) {
    for (const auto& [key, value] : json.at("binds").items()) {
      auto bind = KeyBindParser::parse(actionParser, value);
      if (bind) {
        menu->m_binds.push_back(std::move(bind));
      }
    }
  } else {
    Log::warn("Menu \"%s\" doesn't feature \"binds\" attribute!",
              menu->m_title.c_str());
  }

  return menu;
}

}  // namespace albinjohansson::wanderer

#include "menu_parser.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "action/action.h"
#include "menu_button.h"
#include "pugi_utils.h"

// namespace albinjohansson {
// namespace wanderer {

// namespace {

// void handle_action(ActionID action)
//{
//  switch (action) {
//    case ActionID::GotoHome: {
//    };
//    default:
//      break;
//  }
//}
//
// std::unique_ptr<MenuButton> load_button(const pugi::xml_node& buttonNode)
//{
//  const auto* text = buttonNode.attribute("text").as_string();
//
//  const auto col = buttonNode.attribute("col").as_int();
//  const auto row = buttonNode.attribute("row").as_int();
//  const auto w = buttonNode.attribute("width").as_float();
//  const auto h = buttonNode.attribute("height").as_float();
//
//  // TODO load menu button image paths
//  // const auto imagePath = buttonNode.attribute("image").as_string();
//
//  return std::make_unique<MenuButton>(text, 0, 0, w, h);
//}
//
// std::vector<std::unique_ptr<MenuButton>> load_buttons(
//    const pugi::xml_node& buttonsNode)
//{
//  const auto nButtons = std::distance(buttonsNode.children().begin(),
//                                      buttonsNode.children().end());
//  std::vector<std::unique_ptr<MenuButton>> buttons;
//  buttons.reserve(static_cast<std::size_t>(nButtons));
//
//  for (const auto node : buttonsNode.children("button")) {
//    buttons.push_back(load_button(node));
//  }
//
//  return buttons;
//}
//
//}  // namespace

// std::unique_ptr<IMenu> parse_menu(const char* file)
//{
//  if (!file) {
//    throw std::invalid_argument{"Cannot load menu from null file path!"};
//  }
//
////  const auto document = PugiUtils::LoadDocument(file);
////  const auto rootNode = document.root();
//
//  //  const auto isSubmenu = rootNode.attribute("submenu").as_string();
////  const auto blocking = rootNode.attribute("blocking").as_bool();
////  const auto buttonsRoot = rootNode.child("buttons");
//
//  auto menu = std::make_unique<NewMenu>(file);
//
////  menu->set_blocking(blocking);
////  menu->set_buttons(load_buttons(buttonsRoot));
//
//  return menu;
//}

//}  // namespace wanderer
//}  // namespace albinjohansson
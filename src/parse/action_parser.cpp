#include "action_parser.h"

#include "goto_menu_action.h"
#include "quit_action.h"

using namespace centurion;

namespace albinjohansson::wanderer {
namespace {

inline Maybe<MenuID> menu_id_from_action_id(ActionID action)
{
  switch (action) {
    case ActionID::GotoHome:
      return MenuID::Home;
    case ActionID::GotoSettings:
      return MenuID::Settings;
    case ActionID::GotoControls:
      return MenuID::Controls;
    case ActionID::GotoInGame:
      return MenuID::InGame;
    case ActionID::GotoCredits:
      return MenuID::Credits;
    case ActionID::GotoInventory:
      return MenuID::Inventory;
    case ActionID::Quit:
      [[fallthrough]];
    default:
      return nothing;
  }
}

}  // namespace

ActionParser::ActionParser(WeakPtr<IWandererCore> core,
                           WeakPtr<IMenuStateMachine> menuStateMachine)
    : m_core{core}, m_menuStateMachine{menuStateMachine}
{}

UniquePtr<IAction> ActionParser::parse(const JsonValue& value)
{
  if (value.is_null()) {
    return nullptr;
  }

  const auto id = value.get<ActionID>();

  switch (id) {
    case ActionID::Quit:
      return std::make_unique<QuitAction>(m_core);
    case ActionID::GotoHome:
      [[fallthrough]];
    case ActionID::GotoSettings:
      [[fallthrough]];
    case ActionID::GotoControls:
      [[fallthrough]];
    case ActionID::GotoInGame:
      [[fallthrough]];
    case ActionID::GotoCredits:
      [[fallthrough]];
    case ActionID::GotoInventory: {
      const auto menuID = menu_id_from_action_id(id);
      return std::make_unique<GotoMenuAction>(m_menuStateMachine, *menuID);
    }
    default:
      return nullptr;
  }
}

UniquePtr<IAction> ActionParser::parse(const JsonValue& value, CZString key)
{
  if (!key) {
    return nullptr;
  }

  if (value.count(key)) {
    auto result = parse(value.at(key));
    if (result) {
      return result;
    }
  }

  Log::critical("Failed to parse action \"%s\"!", key);
  return nullptr;
}

}  // namespace albinjohansson::wanderer

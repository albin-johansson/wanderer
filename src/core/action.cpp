#include "action.h"

using namespace nlohmann;

namespace albinjohansson::wanderer {

// TODO implement to_json(json&, ActionID)

void from_json(const json& json, ActionID& action)
{
  const auto id = json.get<std::string>();

  if (id == "Quit") {
    action = ActionID::Quit;

  } else if (id == "GotoHome") {
    action = ActionID::GotoHome;

  } else if (id == "GotoSettings") {
    action = ActionID::GotoSettings;

  } else if (id == "GotoControls") {
    action = ActionID::GotoControls;

  } else if (id == "GotoInGame") {
    action = ActionID::GotoInGame;

  } else if (id == "GotoCredits") {
    action = ActionID::GotoCredits;

  } else {
    throw std::logic_error{"Failed to determine action ID!"};
  }

  // TODO expand
}

}  // namespace albinjohansson::wanderer

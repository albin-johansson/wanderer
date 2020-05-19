#pragma once
#include <json.hpp>

#include "action.h"
#include "menu_state_machine.h"
#include "wanderer_core.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class ActionParser {
 public:
  ActionParser(WeakPtr<IWandererCore> core,
               WeakPtr<IMenuStateMachine> menuStateMachine);

  /**
   * Attempts to parse the supplied JSON value and convert it into an action.
   * This method may return null if no action can be created.
   *
   * Below is an example on how this method should be used.
   * ```
   * ActionParser parser = ...;
   * Json json = ...;
   * const auto action = parser.parse(json.at("action"));
   * ```
   *
   * @param value the JSON value that will be parsed.
   * @return a unique pointer to the created action; null if the action
   * couldn't be created.
   * @since 0.1.0
   */
  UniquePtr<IAction> parse(const JsonValue& value);

 private:
  WeakPtr<IWandererCore> m_core;
  WeakPtr<IMenuStateMachine> m_menuStateMachine;
};

}  // namespace albinjohansson::wanderer
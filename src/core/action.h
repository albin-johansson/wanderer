#pragma once

#include <SDL.h>

#include "input.h"
#include "menu_id.h"
#include "menu_state_machine.h"

namespace albinjohansson::wanderer {

enum class ActionID { GotoHome = 0, GotoSettings, GotoInGame };

// class Action {
//  public:
//   void execute()
//   {

//   }
// };

template <class T>
class Action final {
 private:
  T callable;

 public:
  explicit Action(T callable_) : callable{callable_}
  {}

  void execute() noexcept
  {
    callable();
  }
};

template <class Action>
class KeyBinding {
 private:
  SDL_Scancode code;
  Action action;

 public:
  explicit KeyBinding(SDL_Scancode code_, Action action_) noexcept
      : code{code_}, action{action_}
  {}

  void update(const Input& input) noexcept
  {
    if (input.was_released(code)) {
      action();
    }
  }
};

template <class Action>
auto create_key_binding(SDL_Scancode code, Action action) noexcept
{
  KeyBinding<decltype(action)> binding{code, action};
  return binding;
}

template <class T>
class MenuAction {
 private:
  IMenuStateMachine* stateMachine;
  T callable;

 public:
  explicit MenuAction(IMenuStateMachine* stateMachine_, T callable_)
      : stateMachine{stateMachine_}, callable{callable_}
  {}

  void update(const Input& input) noexcept
  {
    callable(stateMachine, input);
  }
};

}  // namespace albinjohansson::wanderer

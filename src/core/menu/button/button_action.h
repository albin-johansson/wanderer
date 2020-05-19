#pragma once

#include "action.h"
#include "input.h"
#include "menu_button.h"
#include "menu_state_machine.h"

namespace albinjohansson::wanderer {

template <class T>
class ButtonAction final {
 private:
  T callable;

 public:
  explicit ButtonAction(T callable_) : callable{callable_}
  {}

  void update(const Input& input,
              const MenuButton& button,
              IMenuStateMachine* stateMachine)
  {
    callable(input, button, stateMachine);
  }
};

namespace {

template <class T>
inline auto create_button_action(SDL_Scancode code, T callable)
{
  return [=](const Input& input,
             const MenuButton& button,
             IMenuStateMachine* stateMachine) {
    if (input.was_released(code)) {
      const auto mx = input.get_mouse_x();
      const auto my = input.get_mouse_y();
      if (button.contains(mx, my)) {
        callable(stateMachine);
      }
    }
  };
}

template <class T>
inline auto create_button_action(T callable)
{
  return [=](const Input& input,
             const MenuButton& button,
             IMenuStateMachine* stateMachine) {
    const auto mx = input.get_mouse_x();
    const auto my = input.get_mouse_y();
    if (button.contains(mx, my)) {
      callable(stateMachine);
    }
  };
}

inline auto create_set_menu_action(SDL_Scancode code, MenuID menu)
{
  const auto action = create_button_action(
      code,
      [=](IMenuStateMachine* stateMachine) { stateMachine->set_menu(menu); });
  return ButtonAction<decltype(action)>(action);
}

inline auto create_set_menu_action(MenuID menu)
{
  const auto action = create_button_action(
      [=](IMenuStateMachine* stateMachine) { stateMachine->set_menu(menu); });
  return ButtonAction<decltype(action)>(action);
}

}  // namespace

enum GameAction {
  Pause,
  Resume,
  MoveUp,
  MoveRight,
  MoveDown,
  MoveLeft,
  Attack,
  OpenInventory
};

}  // namespace albinjohansson::wanderer
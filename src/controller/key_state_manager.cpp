#include "key_state_manager.h"

namespace albinjohansson::wanderer {

KeyStateManager::KeyStateManager() {
  stateArr = SDL_GetKeyboardState(&nKeys);

  prevStates = std::vector<uint8_t>(nKeys);
  for (int i = 0; i < nKeys; i++) {
    prevStates[i] = 0;
  }
}

KeyStateManager::~KeyStateManager() {
  stateArr = nullptr;
}

void KeyStateManager::copy_states() {
  for (int i = 0; i < nKeys; i++) {
    prevStates.at(i) = stateArr[i];
  }
}

void KeyStateManager::update() {
  copy_states();
}

bool KeyStateManager::is_pressed(SDL_Scancode scancode) const {
  return stateArr[scancode];
}

bool KeyStateManager::was_just_pressed(SDL_Scancode scancode) const {
  return stateArr[scancode] && !prevStates.at(scancode);
}

bool KeyStateManager::was_released(SDL_Scancode scancode) const {
  return !stateArr[scancode] && prevStates.at(scancode);
}

}

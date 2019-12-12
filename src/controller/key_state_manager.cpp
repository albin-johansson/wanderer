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

void KeyStateManager::CopyStates() {
  for (int i = 0; i < nKeys; i++) {
    prevStates.at(i) = stateArr[i];
  }
}

void KeyStateManager::Update() {
  CopyStates();
}

bool KeyStateManager::IsPressed(const SDL_Scancode scancode) const {
  return stateArr[scancode];
}

bool KeyStateManager::WasJustPressed(const SDL_Scancode scancode) const {
  return stateArr[scancode] && !prevStates.at(scancode);
}

bool KeyStateManager::WasReleased(const SDL_Scancode scancode) const {
  return !stateArr[scancode] && prevStates.at(scancode);
}

}

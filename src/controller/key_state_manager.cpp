#include "key_state_manager.h"

namespace wanderer::controller {

KeyStateManager::KeyStateManager() {
  nKeys = 0;
  stateArr = SDL_GetKeyboardState(&nKeys);

  prevStates = std::vector<Uint8>(nKeys);
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

//bool KeyStateManager::IsDown(const SDL_Scancode scancode) const {
//  return false;
//}

bool KeyStateManager::WasReleased(const SDL_Scancode scancode) const {
  return !stateArr[scancode] && prevStates.at(scancode);
}

}

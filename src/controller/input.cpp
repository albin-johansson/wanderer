#include "input.h"
#include "key_state_manager.h"
#include "mouse_state_manager.h"
#include "objects.h"

namespace albinjohansson::wanderer {

Input::Input(std::unique_ptr<KeyStateManager> ksm,
             std::unique_ptr<MouseStateManager> msm) {
  this->keyStateManager = Objects::RequireNonNull(std::move(ksm));
  this->mouseStateManager = Objects::RequireNonNull(std::move(msm));
}

Input::~Input() = default;

void Input::Update() {
  mouseStateManager->Update();
  keyStateManager->Update();
  SDL_PumpEvents();
}

bool Input::IsPressed(SDL_Scancode scancode) const {
  return keyStateManager->IsPressed(scancode);
}

bool Input::WasJustPressed(SDL_Scancode scancode) const {
  return keyStateManager->WasJustPressed(scancode);
}

bool Input::WasReleased(SDL_Scancode scancode) const {
  return keyStateManager->WasReleased(scancode);
}

float Input::GetMouseX() const noexcept {
  return mouseStateManager->GetMouseX();
}

float Input::GetMouseY() const noexcept {
  return mouseStateManager->GetMouseY();
}

bool Input::IsLeftButtonPressed() const noexcept {
  return mouseStateManager->IsLeftButtonPressed();
}

bool Input::IsRightButtonPressed() const noexcept {
  return mouseStateManager->IsRightButtonPressed();
}

bool Input::WasLeftButtonReleased() const noexcept {
  return mouseStateManager->WasLeftButtonReleased();
}

bool Input::WasRightButtonReleased() const noexcept {
  return mouseStateManager->WasRightButtonReleased();
}

bool Input::WasMouseMoved() const noexcept {
  return mouseStateManager->WasMouseMoved();
}

bool Input::WasQuitRequested() const noexcept {
  return SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0;
}

}

#pragma once
#include <memory>

namespace wanderer::controller {

class MouseStateManager;

using MouseStateManager_uptr = std::unique_ptr<MouseStateManager>;
using MouseStateManager_sptr = std::shared_ptr<MouseStateManager>;
using MouseStateManager_wptr = std::weak_ptr<MouseStateManager>;

class MouseStateManager final {
 private:
  float windowWidth = 1;
  float windowHeight = 1;
  float logicalWidth = 1;
  float logicalHeight = 1;

  float oldX = 0;
  float oldY = 0;
  float mouseX = 0;
  float mouseY = 0;
  bool prevLeftPressed = false;
  bool prevRightPressed = false;
  bool leftPressed = false;
  bool rightPressed = false;

 public:
  MouseStateManager();

  ~MouseStateManager();

  static MouseStateManager_uptr Create();

  void Update();

  void SetWindowWidth(int width);

  void SetWindowHeight(int height);

  void SetLogicalWidth(int width);

  void SetLogicalHeight(int logicalHeight);

  [[nodiscard]] inline float GetMouseX() const noexcept {
    return mouseX;
  }

  [[nodiscard]] inline float GetMouseY() const noexcept {
    return mouseY;
  }

  [[nodiscard]] inline bool IsLeftButtonPressed() const noexcept {
    return leftPressed;
  }

  [[nodiscard]] inline bool IsRightButtonPressed() const noexcept {
    return rightPressed;
  }

  [[nodiscard]] inline bool WasLeftButtonReleased() const noexcept {
    return !leftPressed && prevLeftPressed;
  }

  [[nodiscard]] inline bool WasRightButtonReleased() const noexcept {
    return !rightPressed && prevRightPressed;
  }

  [[nodiscard]] bool WasMouseMoved() const noexcept {
    return oldX != mouseX || oldY != mouseY;
  }
};

}

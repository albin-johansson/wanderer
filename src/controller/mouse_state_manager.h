#pragma once
#include <memory>

namespace wanderer::controller {

class MouseStateManager;

using MouseStateManager_uptr = std::unique_ptr<MouseStateManager>;
using MouseStateManager_sptr = std::shared_ptr<MouseStateManager>;
using MouseStateManager_wptr = std::weak_ptr<MouseStateManager>;

class MouseStateManager final {
 private:
  int windowWidth;
  int windowHeight;
  int logicalWidth;
  int logicalHeight;

  int mouseX;
  int mouseY;
  bool prevLeftPressed;
  bool prevRightPressed;
  bool leftPressed;
  bool rightPressed;

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
    return static_cast<float>(mouseX);
  }

  [[nodiscard]] inline float GetMouseY() const noexcept {
    return static_cast<float>(mouseY);
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
};

}

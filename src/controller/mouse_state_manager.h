#pragma once
#include "window_listener.h"

namespace albinjohansson::wanderer {

class MouseStateManager final : public IWindowListener {
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
  MouseStateManager() noexcept;

  ~MouseStateManager() override;

  void WindowUpdated(const Window& window) noexcept override;

  void Update();

  void SetLogicalWidth(int width);

  void SetLogicalHeight(int logicalHeight);

  [[nodiscard]] float GetMouseX() const noexcept;

  [[nodiscard]] float GetMouseY() const noexcept;

  [[nodiscard]] bool IsLeftButtonPressed() const noexcept;

  [[nodiscard]] bool IsRightButtonPressed() const noexcept;

  [[nodiscard]] bool WasLeftButtonReleased() const noexcept;

  [[nodiscard]] bool WasRightButtonReleased() const noexcept;

  [[nodiscard]] bool WasMouseMoved() const noexcept;
};

}

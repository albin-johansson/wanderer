#pragma once
#include "window_listener.h"

namespace albinjohansson::wanderer {

class MouseStateManager final : public centurion::IWindowListener {
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

  void window_updated(const centurion::Window& window) noexcept override;

  void update();

  void set_logical_width(int width);

  void set_logical_height(int logicalHeight);

  [[nodiscard]]
  float get_mouse_x() const noexcept;

  [[nodiscard]]
  float get_mouse_y() const noexcept;

  [[nodiscard]]
  bool is_left_button_pressed() const noexcept;

  [[nodiscard]]
  bool is_right_button_pressed() const noexcept;

  [[nodiscard]]
  bool was_left_button_released() const noexcept;

  [[nodiscard]]
  bool was_right_button_released() const noexcept;

  [[nodiscard]]
  bool was_mouse_moved() const noexcept;
};

}

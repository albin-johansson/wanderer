#pragma once
#include <SDL.h>
#include <string>
#include <vector>

namespace centurion {

class IWindowListener;

/**
 * The Window class is a wrapper around an SDL_Window instance.
 *
 * @since 0.1.0
 */
class Window final {
 private:
  SDL_Window* window = nullptr;
  std::vector<IWindowListener*> windowListeners;

  void notify_window_listeners() noexcept;

 public:
  /**
   * Creates a window instance. The window will be hidden by default.
   *
   * @param title the title of thw window. "Centurion window" by default.
   * @param width the width of the window, must be greater than zero. 800 by default.
   * @param height the height of the window, must be greater than zero. 600 by default.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 0.1.0
   */
  explicit Window(const std::string& title = "Centurion window",
                  int width = 800,
                  int height = 600);

  ~Window();

  /**
   * Makes the window visible. Triggers a window listener update.
   *
   * @since 0.1.0
   */
  void show() noexcept;

  /**
   * Makes the window invisible. Triggers a window listener update.
   *
   * @since 0.1.0
   */
  void hide() noexcept;

  /**
   * Adds a window listener to the window. Null listener are always silently ignored. The window
   * takes no ownership of supplied pointers.
   *
   * @param listener a window listener, may be null.
   * @since 0.1.0
   */
  void add_window_listener(IWindowListener* listener) noexcept;

  /**
   * Sets whether or not the window is in fullscreen mode. Triggers a window listener update.
   *
   * @param fullscreen true if the window should enable fullscreen mode; false
   * otherwise.
   * @since 0.1.0
   */
  void set_fullscreen(bool fullscreen) noexcept;

  /**
   * Sets whether or not the window is decorated. Triggers a window listener update. This property
   * is enabled by default.
   *
   * @param decorated true if the window should be decorated; false otherwise.
   * @since 0.1.0
   */
  void set_decorated(bool decorated) noexcept;

  /**
   * Sets whether or not the window should be resizable. Triggers a window listener update.
   *
   * @param isResizable true if the window should be resizable; false otherwise.
   * @since 0.1.0
   */
  void set_resizable(bool isResizable) noexcept;

  /**
   * Sets the width of the window. Triggers a window listener update.
   *
   * @param width the new width of the window.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void set_width(int width);

  /**
   * Sets the height of the window. Triggers a window listener update.
   *
   * @param height the new height of the window.
   * @throws invalid_argument if the supplied height isn't greater than
   * zero.
   * @since 0.1.0
   */
  void set_height(int height);

  /**
   * Sets the icon that will be used by the window. Triggers a window listener update.
   *
   * @param icon a pointer to the surface that will serve as the icon of the window.
   * @since 0.1.0
   */
  void set_icon(SDL_Surface* icon);

  /**
   * Indicates whether or not the window is resizable.
   *
   * @return true if the window is resizable; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool is_resizable() const noexcept;

  /**
   * Indicates whether or not the window is in fullscreen mode.
   *
   * @return true if the window is in fullscreen mode; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool is_fullscreen() const noexcept;

  /**
   * Indicates whether or not the window is visible.
   *
   * @return true if the window is visible; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool is_visible() const noexcept;

  /**
   * Returns the current width of the window.
   *
   * @return the current width of the window.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_width() const noexcept;

  /**
   * Returns the current height of the window.
   *
   * @return the current height of the window.
   * @since 0.1.0
   */
  [[nodiscard]]
  int get_height() const noexcept;

  /**
   * Returns the title of the window.
   *
   * @return the title of the window.
   * @since 0.1.0
   */
  [[nodiscard]]
  std::string get_title() const noexcept;

  operator SDL_Window*() const noexcept;
};

}
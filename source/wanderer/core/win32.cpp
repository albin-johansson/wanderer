#include "win32.hpp"

#include <SDL_syswm.h>

#include "wanderer/meta/build.hpp"

#if WANDERER_PLATFORM_WINDOWS

#include <dwmapi.h>  // DWMWA_USE_IMMERSIVE_DARK_MODE

#endif  // WANDERER_PLATFORM_WINDOWS

namespace wanderer::win32 {

void use_immersive_dark_mode([[maybe_unused]] cen::window& window)
{
#if WANDERER_PLATFORM_WINDOWS

  SDL_SysWMinfo wm{};
  SDL_VERSION(&wm.version);

  if (SDL_GetWindowWMInfo(window.get(), &wm)) {
    HWND hwnd = wm.info.win.window;

    const cen::shared_object dwmapi{"dwmapi.dll"};

    using signature = HRESULT(HWND, DWORD, LPCVOID, DWORD);
    if (auto* setAttribute = dwmapi.load_function<signature>("DwmSetWindowAttribute")) {
      BOOL mode = 1;
      setAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &mode, sizeof mode);
    }
  }

#endif  // WANDERER_PLATFORM_WINDOWS
}

}  // namespace wanderer::win32
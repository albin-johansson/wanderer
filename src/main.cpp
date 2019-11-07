#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include "renderer.h"
#include "window.h"

using namespace wanderer::view;

int main(int argc, char** argv) {
  std::cout << "HelloWorld!" << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Failed to initialize SDL!" << std::endl;
    return -1;
  } else {
    std::cout << "Success initializing SDL!" << std::endl;
  }

  SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");

  SDL_Event event;
  bool running = true;

  Window window("Wanderer", 1500, 600);
  Renderer renderer(window.GetInternalWindow());

  SDL_Texture* texture = IMG_LoadTexture(renderer.GetInternalRenderer(), "resources/grass.png");

  if (texture != nullptr) {
    std::cout << "Success loading texture!\n";
  }

  window.SetResizable(true);
  std::cout << "Resizable: " << window.IsResizable() << "\n";

  window.Show();

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
        running = false;
        continue;
      }

      if (event.key.keysym.sym == SDLK_f) {
        window.SetFullscreen(true);
      }
    }

    static int x = 10;
    renderer.SetColor(0, 0, 0);
    renderer.Clear();

//    renderer.SetColor(0xFF, 0, 0);
//    renderer.RenderFillRect(x++, 10, 250, 250);
    renderer.RenderTexture(texture, x++, 10, 250, 250);

    renderer.Present();

    SDL_Delay(10);
  }

  window.Hide();

  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }
  SDL_Quit();

  return 0;
}
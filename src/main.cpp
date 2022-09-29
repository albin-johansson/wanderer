#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS
#include <exception>  // set_terminate

#include <centurion/initialization.hpp>
#include <centurion/message_box.hpp>
#include <google/protobuf/stubs/common.h>
#include <spdlog/spdlog.h>

#include "wanderer/core/game.hpp"

using wanderer::Game;

namespace {

struct ProtobufContext final {
  [[nodiscard]] ProtobufContext() { GOOGLE_PROTOBUF_VERIFY_VERSION; }
  ~ProtobufContext() { google::protobuf::ShutdownProtobufLibrary(); }
};

}  // namespace

auto main(int, char*[]) -> int
{
  std::set_terminate([] { std::abort(); });  // Avoid redundant logging

  try {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Booting...");

    ProtobufContext protobuf {};

    cen::sdl sdl;
    cen::ttf sdl_ttf;
    cen::mix sdl_mix;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "letterbox");
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "1");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif  // __APPLE__

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    Game game;
    game.run();

    return EXIT_SUCCESS;
  }
  catch (...) {
    cen::message_box::show(
        "Wanderer crashed :(",
        "Please consider submitting a bug report with reproduction steps.",
        cen::message_box_type::error);
    return EXIT_FAILURE;
  }
}
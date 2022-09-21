#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS
#include <exception>  // set_terminate

#include <centurion/initialization.hpp>
#include <centurion/message_box.hpp>
#include <google/protobuf/stubs/common.h>
#include <spdlog/spdlog.h>

using wanderer::Game;

namespace {

struct ProtobufContext final {
  [[nodiscard]] ProtobufContext() { GOOGLE_PROTOBUF_VERIFY_VERSION; }
  ~ProtobufContext() { google::protobuf::ShutdownProtobufLibrary(); }
};

}  // namespace

int main(int, char*[])
{
  std::set_terminate([] { std::abort(); });  // Avoid redundant logging

  try {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Booting...");

    ProtobufContext protobuf {};

    cen::sdl sdl;
    cen::img sdl_img;
    cen::ttf sdl_ttf;
    cen::mix sdl_mix;

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
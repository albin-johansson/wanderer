#include <cstdlib>    // abort
#include <exception>  // set_terminate
#include <sstream>    // stringstream
#include <vector>     // vector

#include <argparse/argparse.hpp>
#include <centurion.hpp>
#include <google/protobuf/stubs/common.h>

#include "wanderer/core/math.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/io/directories.hpp"
#include "wanderer/meta/build.hpp"
#include "wanderer/misc/assert.hpp"  // Do not remove!
#include "wanderer/misc/exception.hpp"
#include "wanderer/misc/logging.hpp"
#include "wanderer/wanderer_game.hpp"

namespace {

struct protobuf_context final
{
  protobuf_context() { GOOGLE_PROTOBUF_VERIFY_VERSION; }

  ~protobuf_context() { google::protobuf::ShutdownProtobufLibrary(); }
};

[[nodiscard]] auto _make_program_args_parser() -> argparse::ArgumentParser
{
  argparse::ArgumentParser parser{"Wanderer", wanderer::wanderer_version};

  parser.add_argument("--logical-size", "-ls")
      .help("override the logical viewport size")
      .scan<'i', int>()
      .nargs(2);

  parser.add_argument("--tile-size", "-ts")
      .help("override the tile size")
      .scan<'i', int>()
      .nargs(2);

  return parser;
}

}  // namespace

int main(int argc, char** argv)
{
  std::set_terminate([] { std::abort(); }); /* Avoid redundant logging */

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

  try {
    auto parser = _make_program_args_parser();
    parser.parse_args(argc, argv);

    protobuf_context protobuf;

    const cen::sdl sdl;
    const cen::img img;
    const cen::mix mix;
    const cen::ttf ttf;

    wanderer::debug("Persistent file directory is {}",
                    wanderer::get_persistent_file_dir().string());

    auto cfg = wanderer::make_game_cfg();

    if (const auto ls = parser.present<std::vector<int>>("-ls")) {
      cfg.logical_size.x = ls->at(0);
      cfg.logical_size.y = ls->at(1);
      cfg.logical_size_f = wanderer::glmx::as_f(cfg.logical_size);
    }

    if (const auto ts = parser.present<std::vector<int>>("-ts")) {
      cfg.tile_size.x = static_cast<float>(ts->at(0));
      cfg.tile_size.y = static_cast<float>(ts->at(1));
    }

    wanderer::WandererGame game{cfg};
    game.run();

    return 0;
  }
  catch (const std::exception& e) {
    wanderer::print(fmt::color::hot_pink,
                    "Unhandled exception message: '{}'\n",
                    e.what());

    if (const auto* stacktrace = boost::get_error_info<wanderer::TraceInfo>(e)) {
      std::stringstream stream;
      stream << *stacktrace;
      wanderer::print(fmt::color::hot_pink, "{}\n", stream.str());
    }

    std::abort();
  }
}
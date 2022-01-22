#include <cstdlib>    // abort
#include <exception>  // set_terminate

#include <centurion.hpp>
#include <fmt/ostream.h>

#include "assert.hpp"  // Do not remove!
#include "exception.hpp"
#include "io/directories.hpp"
#include "logging.hpp"
#include "wanderer_game.hpp"

int main(int, char**)
{
  std::set_terminate([] { std::abort(); }); /* Avoid redundant logging */

  try {
    const cen::sdl sdl;
    const cen::img img;
    const cen::mix mix;
    const cen::ttf ttf;

    wanderer::log_debug("Persistent file directory is {}",
                        wanderer::get_persistent_file_dir());

    wanderer::wanderer_game game;
    game.run();

    return 0;
  }
  catch (const std::exception& e) {
    wanderer::print(fmt::color::hot_pink,
                    "Unhandled exception message: '{}'\n",
                    e.what());

    if (const auto* stacktrace = boost::get_error_info<wanderer::trace_info>(e)) {
      wanderer::print(fmt::color::hot_pink, "{}\n", *stacktrace);
    }

    std::abort();
  }
}
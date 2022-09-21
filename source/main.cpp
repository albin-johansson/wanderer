#include <cstdlib>    // abort
#include <exception>  // set_terminate
#include <sstream>    // stringstream
#include <vector>     // vector

#include <argparse/argparse.hpp>
#include <centurion.hpp>
#include <google/protobuf/stubs/common.h>

namespace {

struct ProtobufContext final
{
  [[nodiscard]] ProtobufContext() { GOOGLE_PROTOBUF_VERIFY_VERSION; }
  ~ProtobufContext() { google::protobuf::ShutdownProtobufLibrary(); }
};

}  // namespace

int main(int, char*[])
{
  std::set_terminate([] { std::abort(); });  // Avoid redundant logging

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

  ProtobufContext protobuf{};
}
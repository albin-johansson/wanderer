#include "files.hpp"

#include <fstream>   // ifstream
#include <ios>       // ios
#include <iterator>  // istreambuf_iterator
#include <string>    // string

namespace wanderer {

auto load_file_into_string(const char* filename) -> String
{
  std::ifstream stream {filename, std::ios::in};
  std::string contents {std::istreambuf_iterator {stream},
                        std::istreambuf_iterator<char> {}};
  return from_std(contents);
}

}  // namespace wanderer

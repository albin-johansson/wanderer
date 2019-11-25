#pragma once
#include <string>

namespace albinjohansson::wanderer {

class TiledMapParser {
 private:

 public:
  explicit TiledMapParser(const std::string& file);

  ~TiledMapParser();
};

}

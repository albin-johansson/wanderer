#pragma once
#include <string>
#include <map>

namespace albinjohansson::tiled {

class TiledObject final {
 private:
  std::map<std::string, std::string> attributes;
 public:
  TiledObject();

  ~TiledObject();

  void AddProperty(const std::string& id, const std::string& value);

  const std::string& GetAttribute(const std::string& id) const;

  bool HasAttribute(const std::string& id) const;
};

}

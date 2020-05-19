#include "pugi_utils.h"

#include "wanderer_exception.h"

namespace albinjohansson::wanderer {

pugi::xml_document PugiUtils::LoadDocument(const std::string& path)
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (!result) {
    throw WandererException{"Failed to load: " + path +
                            ", Error:" + result.description()};
  }
  return doc;
}

}  // namespace albinjohansson::wanderer

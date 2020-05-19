#include "key_bind_parser.h"

#include "json_utils.h"

using namespace centurion;

namespace wanderer {

UniquePtr<KeyBind> KeyBindParser::parse(ActionParser& actionParser,
                                        const JSONValue& json)
{
  const auto keyStr = maybe_get<std::string>(json, "key");
  if (!keyStr) {
    Log::critical("Key bind must have \"key\" attribute!");
    return nullptr;
  }

  const Key key = SDL_GetKeyFromName(keyStr->c_str());  // TODO CTN 4.1

  if (key.scancode() == SDL_SCANCODE_UNKNOWN) {
    Log::critical("Didn't recognize the key \"%s\"!", keyStr->c_str());
    return nullptr;
  }

  const auto trigger = maybe_get<KeyBind::Trigger>(json, "trigger");
  if (!trigger) {
    Log::critical("Failed to deduce key bind trigger!");
    return nullptr;
  }

  auto action = actionParser.parse(json, "action");
  if (!action) {
    return nullptr;
  }

  return std::make_unique<KeyBind>(std::move(action), key, *trigger);
}

}  // namespace wanderer

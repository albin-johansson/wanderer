#include "sound_engine_parser.h"

#include "json_utils.h"
#include "wanderer_exception.h"

using namespace centurion;

namespace wanderer {
namespace {

UniquePtr<SoundEffect> parse_sound_effect(const JSONValue& json)
{
  const auto file = maybe_get<std::string>(json, "file");
  if (file) {
    auto sound = SoundEffect::unique(file->c_str());
    sound->set_volume(
        maybe_get<int>(json, "volume").value_or(SoundEffect::max_volume()));
    return sound;
  } else {
    Log::warn("Failed to find file attribute when parsing sound effect!");
    return nullptr;
  }
}

}  // namespace

UniquePtr<SoundEngine> SoundEngineParser::parse(CZString file)
{
  if (!file) {
    throw WandererException{"Cannot create sound engine from null file!"};
  }

  JSON json = parse_json(file);
  auto engine = UniquePtr<SoundEngine>(new SoundEngine{});

  if (json.count("sounds")) {
    for (const auto& [key, value] : json.at("sounds").items()) {
      const auto id = maybe_get<SoundID>(value, "id");
      if (!id) {
        Log::warn("Failed to find ID attribute when parsing sound effect!");
        continue;
      }

      auto sound = parse_sound_effect(value);
      if (sound) {
        engine->m_sounds.emplace(*id, std::move(sound));
      }
    }

  } else {
    Log::warn("Couldn't find \"sounds\" attribute when parsing sound effects!");
  }

  return engine;
}

}  // namespace wanderer
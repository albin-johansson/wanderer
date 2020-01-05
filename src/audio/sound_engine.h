#pragma once
#include <unordered_map>
#include <string>
#include <memory>

namespace centurion {

class SoundEffect;

}

namespace albinjohansson::wanderer {

class SoundEngine final {
 private:
  std::unordered_map<std::string, std::unique_ptr<centurion::SoundEffect>> sounds;

  void load_sounds(const std::string& file);

  void registerSound(const std::string& id, std::unique_ptr<centurion::SoundEffect> sound);

 public:
  explicit SoundEngine(const std::string& file);

  ~SoundEngine();

  [[nodiscard]]
  centurion::SoundEffect& get_sound(const std::string& id) const noexcept;
};

}

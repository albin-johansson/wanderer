#pragma once
#include <unordered_map>
#include <string>
#include <memory>

namespace albinjohansson::wanderer {

class SoundEffect;

class SoundEngine final { // TODO expand
 private:
  std::unordered_map<std::string, std::unique_ptr<SoundEffect>> sounds;
  bool enabled = true;

  void load_sounds(const std::string& file);

  void registerSound(const std::string& id, std::unique_ptr<SoundEffect> sound);

 public:
  explicit SoundEngine(const std::string& file);

  ~SoundEngine();

  void play(const std::string& id);

  void set_enabled(bool enabled) noexcept;

  [[nodiscard]]
  bool is_enabled() const noexcept;
};

}

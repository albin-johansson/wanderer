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

  void LoadSounds(const std::string& file);

  void Register(const std::string& id, std::unique_ptr<SoundEffect> sound);

 public:
  explicit SoundEngine(const std::string& file);

  ~SoundEngine();

  void Play(const std::string& id);

  void SetEnabled(bool enabled) noexcept;

  [[nodiscard]]
  bool IsEnabled() const noexcept;
};

}

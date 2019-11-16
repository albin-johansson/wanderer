#pragma once
#include <SDL_mixer.h>
#include <string>
#include <memory>

namespace wanderer::audio {

// TODO add fade effects

class SoundEffect;

using SoundEffect_uptr = std::unique_ptr<SoundEffect>;
using SoundEffect_sptr = std::shared_ptr<SoundEffect>;
using SoundEffect_wptr = std::weak_ptr<SoundEffect>;

/**
 * The SoundEffect class represents sound effects in various file formats.
 *
 * @since 0.1.0
 */
class SoundEffect final {
 private:
  static constexpr int UNDEFINED_CHANNEL = -1;

  Mix_Chunk* chunk = nullptr;
  int channel = UNDEFINED_CHANNEL;

  /**
   * Activates the sound effect by playing it the specified amount of times.
   *
   * @param nLoops the amount of times to play the sound effect.
   * @since 0.1.0
   */
  void Activate(int nLoops) noexcept;

 public:
  /**
   * @param file the file path of the audio file.
   * @throws BadStateException if the audio file cannot be loaded.
   * @since 0.1.0
   */
  explicit SoundEffect(const std::string& file);

  ~SoundEffect();

  /**
   * Creates and returns a unique pointer to a sound effect instance.
   *
   * @param file the file path of the audio file.
   * @throws BadStateException if the audio file cannot be loaded.
   * @since 0.1.0
   */
  static SoundEffect_uptr Create(const std::string& file);

  /**
   * Plays the sound effect.
   *
   * @since 0.1.0
   */
  void Play() noexcept;

  /**
   * Loops the sound effect by the specified amount of times.
   *
   * @param nLoops the amount of loops. A negative value indicates that the sound effect should
   * be looped indefinitely.
   * @since 0.1.0
   */
  void Loop(int nLoops) noexcept;

  /**
   * Stops the sound effect from playing.
   *
   * @since 0.1.0
   */
  void Stop() noexcept;

  /**
   * Sets the volume of the sound effect.
   *
   * @param volume the volume of the sound effect, in the range [0, MIX_MAX_VOLUME].
   * @since 0.1.0
   */
  void SetVolume(int volume) noexcept;

  /**
   * Returns the current volume of the sound effect.
   *
   * @return the current volume of the sound effect.
   * @since 0.1.0
   */
  [[nodiscard]] inline int GetVolume() const noexcept {
    return chunk->volume;
  }
};

}
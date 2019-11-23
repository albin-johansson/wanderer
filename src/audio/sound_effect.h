#pragma once
#include <SDL_mixer.h>
#include <string>
#include <memory>

namespace albinjohansson::wanderer {

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
   * Fades in the sound effect. This method has no effect if the supplied duration isn't greater
   * than zero or if the sound effect is currently playing.
   *
   * @param ms the duration to fade in, in milliseconds.
   * @since 0.1.0
   */
  void FadeIn(Uint32 ms) noexcept;

  /**
   * Fades out the sound effect. This method has no effect if the supplied duration isn't greater
   * than zero or if the sound effect isn't currently playing.
   *
   * @param ms the duration to fade in, in milliseconds.
   * @since 0.1.0
   */
  void FadeOut(Uint32 ms) noexcept;

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

  /**
   * Indicates whether or not the sound effect is currently playing.
   *
   * @return true if the sound effect is playing; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] inline bool IsPlaying() const noexcept {
    return (channel != UNDEFINED_CHANNEL) && Mix_Playing(channel);
  }
};

}

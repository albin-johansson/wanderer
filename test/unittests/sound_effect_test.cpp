#include "catch.hpp"
#include "sound_effect.h"
#include "bad_state_exception.h"

using namespace albinjohansson::wanderer;

TEST_CASE("SoundEffect::SoundEffect", "[SoundEffect]") {
  CHECK_THROWS_AS(SoundEffect("somebadpath"), BadStateException);
}

TEST_CASE("SoundEffect::Play && SoundEffect::Stop", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");

  CHECK(!sound.IsPlaying());

  sound.SetVolume(1);
  sound.Loop(10);

  CHECK(sound.IsPlaying());

  sound.Stop();
  CHECK(!sound.IsPlaying());
}

TEST_CASE("SoundEffect::FadeIn && SoundEffect::FadeOut", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");

  CHECK_NOTHROW(sound.FadeIn(0));
  CHECK_NOTHROW(sound.FadeIn(-1));

  CHECK_NOTHROW(sound.FadeOut(0));
  CHECK_NOTHROW(sound.FadeOut(-1));
}

TEST_CASE("SoundEffect::Loop", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");
  sound.SetVolume(1);

  sound.Loop(10);
  CHECK(sound.IsPlaying());
  sound.Stop();

  CHECK(SoundEffect::LOOP_INDEFINITELY < 0);

  CHECK_NOTHROW(sound.Loop(SoundEffect::LOOP_INDEFINITELY));
  CHECK(sound.IsPlaying());

  sound.Stop();
  CHECK(!sound.IsPlaying());
}

TEST_CASE("SoundEffect::SetVolume && SoundEffect::GetVolume", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");

  sound.SetVolume(MIX_MAX_VOLUME);
  CHECK(sound.GetVolume() == MIX_MAX_VOLUME);

  sound.SetVolume(-1);
  CHECK(sound.GetVolume() == 0);

  sound.SetVolume(MIX_MAX_VOLUME + 1);
  CHECK(sound.GetVolume() == MIX_MAX_VOLUME);
}

TEST_CASE("SoundEffect::IsPlaying", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");

  CHECK(!sound.IsPlaying());
  sound.SetVolume(1); // So that I don't scare myself...
  sound.Loop(2);
  CHECK(sound.IsPlaying());
}
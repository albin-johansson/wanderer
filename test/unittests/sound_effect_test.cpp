#include "catch.hpp"
#include "sound_effect.h"
#include "centurion_exception.h"

using namespace centurion;

TEST_CASE("SoundEffect::SoundEffect", "[SoundEffect]") {
  CHECK_THROWS_AS(SoundEffect("somebadpath"), CenturionException);
}

TEST_CASE("SoundEffect::Play && SoundEffect::Stop", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");

  CHECK(!sound.is_playing());

  sound.set_volume(1);
  sound.loop(10);

  CHECK(sound.is_playing());

  sound.stop();
  CHECK(!sound.is_playing());
}

TEST_CASE("SoundEffect::FadeIn && SoundEffect::FadeOut", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");

  CHECK_NOTHROW(sound.fade_in(0));
  CHECK_NOTHROW(sound.fade_in(-1));

  CHECK_NOTHROW(sound.fade_out(0));
  CHECK_NOTHROW(sound.fade_out(-1));
}

TEST_CASE("SoundEffect::Loop", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");
  sound.set_volume(1);

  sound.loop(10);
  CHECK(sound.is_playing());
  sound.stop();

  CHECK(SoundEffect::loopIndefinitely < 0);

  CHECK_NOTHROW(sound.loop(SoundEffect::loopIndefinitely));
  CHECK(sound.is_playing());

  sound.stop();
  CHECK(!sound.is_playing());
}

TEST_CASE("SoundEffect::SetVolume && SoundEffect::GetVolume", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");

  sound.set_volume(MIX_MAX_VOLUME);
  CHECK(sound.get_volume() == MIX_MAX_VOLUME);

  sound.set_volume(-1);
  CHECK(sound.get_volume() == 0);

  sound.set_volume(MIX_MAX_VOLUME + 1);
  CHECK(sound.get_volume() == MIX_MAX_VOLUME);
}

TEST_CASE("SoundEffect::IsPlaying", "[SoundEffect]") {
  SoundEffect sound("resources/audio/swing.wav");

  CHECK(!sound.is_playing());
  sound.set_volume(1); // So that I don't scare myself...
  sound.loop(2);
  CHECK(sound.is_playing());
}
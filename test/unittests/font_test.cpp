#include "catch.hpp"
#include "font.h"
#include "bad_state_exception.h"

using namespace albinjohansson::wanderer;

TEST_CASE("Font(string&, int)", "[Font]") {
  CHECK_THROWS_AS(Font("", 1), BadStateException);
  CHECK_THROWS_AS(Font("", 0), std::invalid_argument);
}

TEST_CASE("Font::Reset", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  f.set_bold(true);
  f.set_italic(true);
  f.set_underlined(true);
  f.set_strikethrough(true);

  f.reset();
  CHECK(!f.is_bold());
  CHECK(!f.is_italic());
  CHECK(!f.is_underlined());
  CHECK(!f.is_strikethrough());
}

TEST_CASE("Font::SetBold", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.is_bold());

  f.set_bold(true);
  CHECK(f.is_bold());

  f.set_bold(false);
  CHECK(!f.is_bold());
}

TEST_CASE("Font::SetItalic", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.is_italic());

  f.set_italic(true);
  CHECK(f.is_italic());

  f.set_italic(false);
  CHECK(!f.is_italic());
}

TEST_CASE("Font::SetUnderlined", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.is_underlined());

  f.set_underlined(true);
  CHECK(f.is_underlined());

  f.set_underlined(false);
  CHECK(!f.is_underlined());
}

TEST_CASE("Font::SetStrikethrough", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.is_strikethrough());

  f.set_strikethrough(true);
  CHECK(f.is_strikethrough());

  f.set_strikethrough(false);
  CHECK(!f.is_strikethrough());
}

TEST_CASE("Font::SetOutlined", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.is_outlined());

  f.set_outlined(true);
  CHECK(f.is_outlined());

  f.set_outlined(false);
  CHECK(!f.is_outlined());
}

TEST_CASE("Font::GetSize", "[Font]") {
  int size = 12;
  Font f("resources/font/type_writer.ttf", size);

  CHECK(size == f.get_size());
}

TEST_CASE("Font::IsFixedWidth", "[Font]") {
  Font firacode("resources/font/fira_code.ttf", 12); // Fixed width
  Font daniel("resources/font/daniel.ttf", 12);      // Not fixed width

  CHECK(firacode.is_fixed_width());
  CHECK(!daniel.is_fixed_width());
}

TEST_CASE("Font::GetInternalFont", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);
  CHECK(f.GetInternalFont() != nullptr);
}

TEST_CASE("Font::GetFamilyName", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);
  CHECK(f.get_family_name() == "Type Writer");
}

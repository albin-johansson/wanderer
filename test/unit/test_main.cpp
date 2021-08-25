#include <gtest/gtest.h>

#include <centurion.hpp>

#include "io/rune_configuration.hpp"

int main(int argc, char** argv)
{
  cen::library centurion;
  cen::log::use_preset_output_function();

  wanderer::prepare_rune_configuration();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

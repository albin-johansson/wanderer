#include <gtest/gtest.h>

#include <centurion.hpp>

#include "io/rune_configuration.hpp"

int main(int argc, char** argv)
{
  cen::library centurion;
  cen::log::use_preset_output_function();
  cen::log::set_priority(cen::log_priority::debug);

  wanderer::PrepareRuneConfiguration();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

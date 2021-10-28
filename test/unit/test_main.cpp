#include <gtest/gtest.h>

#include <centurion.hpp>

int main(int argc, char** argv)
{
  cen::library centurion;
  cen::log::use_preset_output_function();
  cen::log::set_priority(cen::log_priority::debug);

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include "systems/input/dev_console_system.hpp"

#include <gtest/gtest.h>

using namespace wanderer;

TEST(DevConsole, ParseSetTimeCommand)
{
  ASSERT_TRUE(sys::ParseSetTimeCommand("settime 00:00"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("settime 23:59"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("settime 10:20"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("settime 09:05"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("settime 13:45"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("settime 19:00"));

  ASSERT_FALSE(sys::ParseSetTimeCommand("settime"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("settime 25:00"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("settime 30:00"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("settime 24:00"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("settime 23:60"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("settime 0:00"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("settime 00:0"));

  {
    const auto result = sys::ParseSetTimeCommand("settime 19:52");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(19, result->hour);
    ASSERT_EQ(52, result->minutes);
  }

  {
    const auto result = sys::ParseSetTimeCommand("settime 07:40");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(7, result->hour);
    ASSERT_EQ(40, result->minutes);
  }
}

TEST(DevConsole, ParseSetDayCommand)
{
  ASSERT_EQ(DayOfWeek::Monday, sys::ParseSetDayCommand("setday mon"));
  ASSERT_EQ(DayOfWeek::Tuesday, sys::ParseSetDayCommand("setday tue"));
  ASSERT_EQ(DayOfWeek::Wednesday, sys::ParseSetDayCommand("setday wed"));
  ASSERT_EQ(DayOfWeek::Thursday, sys::ParseSetDayCommand("setday thu"));
  ASSERT_EQ(DayOfWeek::Friday, sys::ParseSetDayCommand("setday fri"));
  ASSERT_EQ(DayOfWeek::Saturday, sys::ParseSetDayCommand("setday sat"));
  ASSERT_EQ(DayOfWeek::Sunday, sys::ParseSetDayCommand("setday sun"));

  ASSERT_FALSE(sys::ParseSetDayCommand("setday"));
  ASSERT_FALSE(sys::ParseSetDayCommand("setday MON"));
  ASSERT_FALSE(sys::ParseSetDayCommand("setday tuE"));
}

TEST(DevConsole, ParseEnterCommand)
{
  ASSERT_EQ(0, sys::ParseEnterCommand("enter 0"));
  ASSERT_EQ(1, sys::ParseEnterCommand("enter 1"));
  ASSERT_EQ(42, sys::ParseEnterCommand("enter 42"));

  ASSERT_FALSE(sys::ParseEnterCommand("enter"));
  ASSERT_FALSE(sys::ParseEnterCommand("enter abc"));
}
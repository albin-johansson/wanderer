#include "systems/input/dev_console_system.hpp"

#include <gtest/gtest.h>

using namespace wanderer;

TEST(DevConsole, ParseSetTimeCommand)
{
  ASSERT_TRUE(sys::ParseSetTimeCommand("set-time 00:00"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("set-time 23:59"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("set-time 10:20"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("set-time 09:05"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("set-time 13:45"));
  ASSERT_TRUE(sys::ParseSetTimeCommand("set-time 19:00"));

  ASSERT_FALSE(sys::ParseSetTimeCommand("set-time"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("set-time 25:00"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("set-time 30:00"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("set-time 24:00"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("set-time 23:60"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("set-time 0:00"));
  ASSERT_FALSE(sys::ParseSetTimeCommand("set-time 00:0"));

  {
    const auto result = sys::ParseSetTimeCommand("set-time 19:52");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(19, result->hour);
    ASSERT_EQ(52, result->minutes);
  }

  {
    const auto result = sys::ParseSetTimeCommand("set-time 07:40");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(7, result->hour);
    ASSERT_EQ(40, result->minutes);
  }
}

TEST(DevConsole, ParseSetDayCommand)
{
  ASSERT_EQ(DayOfWeek::Monday, sys::ParseSetDayCommand("set-day mon"));
  ASSERT_EQ(DayOfWeek::Tuesday, sys::ParseSetDayCommand("set-day tue"));
  ASSERT_EQ(DayOfWeek::Wednesday, sys::ParseSetDayCommand("set-day wed"));
  ASSERT_EQ(DayOfWeek::Thursday, sys::ParseSetDayCommand("set-day thu"));
  ASSERT_EQ(DayOfWeek::Friday, sys::ParseSetDayCommand("set-day fri"));
  ASSERT_EQ(DayOfWeek::Saturday, sys::ParseSetDayCommand("set-day sat"));
  ASSERT_EQ(DayOfWeek::Sunday, sys::ParseSetDayCommand("set-day sun"));

  ASSERT_FALSE(sys::ParseSetDayCommand("set-day"));
  ASSERT_FALSE(sys::ParseSetDayCommand("set-day MON"));
  ASSERT_FALSE(sys::ParseSetDayCommand("set-day tuE"));
}

TEST(DevConsole, ParseEnterCommand)
{
  ASSERT_EQ(0, sys::ParseEnterCommand("enter 0"));
  ASSERT_EQ(1, sys::ParseEnterCommand("enter 1"));
  ASSERT_EQ(42, sys::ParseEnterCommand("enter 42"));

  ASSERT_FALSE(sys::ParseEnterCommand("enter"));
  ASSERT_FALSE(sys::ParseEnterCommand("enter abc"));
}
#include <gtest/gtest.h>

#include "core/aliases/float2.hpp"
#include "core/math/angles.hpp"

using namespace wanderer;

// TODO point_at

TEST(Vector2, Defaults)
{
  const float2 vec;
  EXPECT_FLOAT_EQ(0, vec.x);
  EXPECT_FLOAT_EQ(0, vec.y);
  EXPECT_FLOAT_EQ(0, vec.magnitude());
  EXPECT_TRUE(vec.is_zero());
}

TEST(Vector2, Constructor)
{
  const auto x = 112.9f;
  const auto y = 8254.3f;
  const float2 vec{x, y};
  EXPECT_FLOAT_EQ(x, vec.x);
  EXPECT_FLOAT_EQ(y, vec.y);
}

TEST(Vector2, Scale)
{
  float2 vector;

  vector.scale(7);  // scaling zeroed vector
  EXPECT_TRUE(vector.is_zero());

  const auto x = 745;
  const auto y = -1834;
  vector.x = x;
  vector.y = y;

  EXPECT_FLOAT_EQ(x, vector.x);
  EXPECT_FLOAT_EQ(y, vector.y);

  const auto scale = 82;
  vector.scale(scale);

  EXPECT_FLOAT_EQ(x * scale, vector.x);
  EXPECT_FLOAT_EQ(y * scale, vector.y);
}

TEST(Vector2, Norm)
{
  {  // Normalize the zero vector
    float2 vector;
    vector.norm();  // no effect on the zero vector
    EXPECT_FALSE(vector.is_unit());
    EXPECT_TRUE(vector.is_zero());
  }

  {  // Normalize non-zero vector
    float2 vector{42, 124};
    EXPECT_FALSE(vector.is_unit());

    vector.norm();
    EXPECT_TRUE(vector.is_unit());
  }
}

TEST(Vector2, Reset)
{
  float2 vector{849, 241};
  EXPECT_FALSE(vector.is_zero());

  vector.reset();
  EXPECT_TRUE(vector.is_zero());
}

TEST(Vector2, SetMagnitude)
{
  {  // Normal magnitude
    float2 vector{1283, 881};
    vector.set_magnitude(433);
    EXPECT_FLOAT_EQ(433, vector.magnitude());
  }

  {  // Create unit vector
    float2 vector{849, 241};
    vector.set_magnitude(1);
    EXPECT_TRUE(vector.is_unit());
  }

  {  // Zero magnitude
    float2 vector{849, 241};
    vector.set_magnitude(0);
    EXPECT_TRUE(vector.is_zero());
  }

  {  // Negative magnitude
    float2 vector{849, 241};
    vector.set_magnitude(-1);
    EXPECT_TRUE(vector.is_zero());
  }
}

TEST(Vector2, Lerp)
{
  const auto x = 123;
  const auto y = 456;

  float2 fst{x, y};
  const float2 snd{834, 432};

  const auto alpha = 0.8;
  const auto invAlpha = 1 - alpha;

  fst.lerp(snd, alpha);

  EXPECT_FLOAT_EQ(x * invAlpha + snd.x * alpha, fst.x);
  EXPECT_FLOAT_EQ(y * invAlpha + snd.y * alpha, fst.y);
}

TEST(Vector2, LerpSmooth)
{
  float2 fst{123, 456};
  const float2 snd{834, 432};
  EXPECT_NO_THROW(fst.lerp_smooth(snd, 0.45));  // just check that it compiles
}

TEST(Vector2, Negate)
{
  float2 vector{20, 30};

  vector.negate();
  EXPECT_FLOAT_EQ(-20, vector.x);
  EXPECT_FLOAT_EQ(-30, vector.y);

  vector.negate();
  EXPECT_FLOAT_EQ(20, vector.x);
  EXPECT_FLOAT_EQ(30, vector.y);
}

TEST(Vector2, AdditionAssignment)
{
  const auto x = 20;
  const auto y = 30;

  float2 fst{x, y};
  const float2 snd{45, -14};

  fst += snd;

  EXPECT_FLOAT_EQ(x + snd.x, fst.x);
  EXPECT_FLOAT_EQ(y + snd.y, fst.y);
}

TEST(Vector2, SubtractionAssignment)
{
  const auto x = 83;
  const auto y = 55;

  float2 fst{x, y};
  const float2 snd{-35, 77};

  fst -= snd;

  EXPECT_FLOAT_EQ(x - snd.x, fst.x);
  EXPECT_FLOAT_EQ(y - snd.y, fst.y);
}

TEST(Vector2, Distance)
{
  {  // Distance to self
    const float2 vector{783, 334};
    EXPECT_FLOAT_EQ(0, distance(vector, vector));
  }

  {  // Normal vectors
    const float2 fst{1892.0f, 4412.0f};
    const float2 snd{442.0f, 266.0f};

    const auto expected = 4392.24;  // obtained from wolfram alpha

    EXPECT_NEAR(expected, distance(fst, snd), 0.01f);
    EXPECT_NEAR(distance(fst, snd), expected, 0.01f);
  }
}

TEST(Vector2, Cross)
{
  const float2 fst{123, 456};
  const float2 snd{789, 434};
  EXPECT_FLOAT_EQ(0, cross(fst, fst));

  // Expected values obtained from wolfram alpha
  EXPECT_FLOAT_EQ(-306'402, cross(fst, snd));
  EXPECT_FLOAT_EQ(306'402, cross(snd, fst));
}

TEST(Vector2, Angle)
{
  {  // Angle to self
    const float2 vector{1283, 9123};
    EXPECT_FLOAT_EQ(0, angle(vector, vector));
  }

  {  // Small vectors
    const float2 fst{50, 25};
    const float2 snd{5, 10};

    // Obtained with wolfram alpha
    const auto expected = std::acos(4.0 / 5.0);

    EXPECT_FLOAT_EQ(expected, angle(fst, snd));
    EXPECT_FLOAT_EQ(-expected, angle(snd, fst));
  }

  {  // Big vectors
    const float2 fst{63'112, 58'124};
    const float2 snd{30'979, 77'437};

    // Obtained with wolfram alpha
    const auto expected = 0.5 * (pi - 2 * std::atan(1614023709.0 / 771645137.0));

    EXPECT_FLOAT_EQ(expected, angle(fst, snd));
    EXPECT_FLOAT_EQ(-expected, angle(snd, fst));
  }

  {  // With the zero vector
    const float2 zero;
    const float2 nonZero{123, 123};
    EXPECT_FLOAT_EQ(0, angle(zero, zero));
    EXPECT_FLOAT_EQ(0, angle(zero, nonZero));
    EXPECT_FLOAT_EQ(0, angle(nonZero, zero));
  }
}

TEST(Vector2, Addition)
{
  const float2 fst(25, 83);
  const float2 snd(93, 12);

  const auto sum = fst + snd;
  EXPECT_FLOAT_EQ(fst.x + snd.x, sum.x);
  EXPECT_FLOAT_EQ(fst.y + snd.y, sum.y);
}

TEST(Vector2, Subtraction)
{
  const float2 fst(831, -472);
  const float2 snd(185, 442);

  const auto diff1 = fst - snd;
  const auto diff2 = snd - fst;

  EXPECT_FLOAT_EQ(fst.x - snd.x, diff1.x);
  EXPECT_FLOAT_EQ(fst.y - snd.y, diff1.y);

  EXPECT_FLOAT_EQ(snd.x - fst.x, diff2.x);
  EXPECT_FLOAT_EQ(snd.y - fst.y, diff2.y);
}

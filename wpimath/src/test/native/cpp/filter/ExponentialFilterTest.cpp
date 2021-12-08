// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/filter/ExponentialFilter.h"
#include "gtest/gtest.h"

TEST(MedianFilterTest, MedianFilterNotFullTestEven) {
  frc::ExponentialFilter<double> filter(1.0);

  filter.Calculate(3);
  filter.Calculate(0);
  filter.Calculate(4);

  EXPECT_EQ(filter.Calculate(5), 5);
}

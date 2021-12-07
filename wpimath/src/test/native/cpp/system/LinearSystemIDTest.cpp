// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/system/LinearSystem.h>
#include <frc/system/plant/DCMotor.h>
#include <frc/system/plant/LinearSystemId.h>
#include <gtest/gtest.h>

#include "frc/system/plant/LinearSystemId.h"
#include "units/length.h"
#include "units/mass.h"

TEST(LinearSystemIDTest, IdentifyDrivetrainVelocitySystem) {
  auto model = frc::LinearSystemId::DrivetrainVelocitySystem(
      frc::DCMotor::NEO(4), 70_kg, 0.05_m, 0.4_m, 6.0_kg_sq_m, 6.0);

  ASSERT_TRUE(model.A().isApprox(
      Eigen::Matrix<double, 2, 2>{{-10.14132, 3.06598}, {3.06598, -10.14132}},
      0.001));
  ASSERT_TRUE(model.B().isApprox(
      Eigen::Matrix<double, 2, 2>{{4.2590, -1.28762}, {-1.2876, 4.2590}},
      0.001));
  ASSERT_TRUE(model.C().isApprox(
      Eigen::Matrix<double, 2, 2>{{1.0, 0.0}, {0.0, 1.0}}, 0.001));
  ASSERT_TRUE(model.D().isApprox(
      Eigen::Matrix<double, 2, 2>{{0.0, 0.0}, {0.0, 0.0}}, 0.001));
}

TEST(LinearSystemIDTest, ElevatorSystem) {
  auto model = frc::LinearSystemId::ElevatorSystem(frc::DCMotor::NEO(2), 5_kg,
                                                   0.05_m, 12);
  ASSERT_TRUE(model.A().isApprox(
      Eigen::Matrix<double, 2, 2>{{0.0, 1.0}, {0.0, -99.05473}}, 0.001));
  ASSERT_TRUE(
      model.B().isApprox(Eigen::Matrix<double, 2, 1>{0.0, 20.8}, 0.001));
  ASSERT_TRUE(model.C().isApprox(Eigen::Matrix<double, 1, 2>{1.0, 0.0}, 0.001));
  ASSERT_TRUE(model.D().isApprox(Eigen::Matrix<double, 1, 1>{0.0}, 0.001));
}

TEST(LinearSystemIDTest, FlywheelSystem) {
  auto model = frc::LinearSystemId::FlywheelSystem(frc::DCMotor::NEO(2),
                                                   0.00032_kg_sq_m, 1.0);
  ASSERT_TRUE(
      model.A().isApprox(Eigen::Matrix<double, 1, 1>{-26.87032}, 0.001));
  ASSERT_TRUE(
      model.B().isApprox(Eigen::Matrix<double, 1, 1>{1354.166667}, 0.001));
  ASSERT_TRUE(model.C().isApprox(Eigen::Matrix<double, 1, 1>{1.0}, 0.001));
  ASSERT_TRUE(model.D().isApprox(Eigen::Matrix<double, 1, 1>{0.0}, 0.001));
}

TEST(LinearSystemIDTest, IdentifyPositionSystem) {
  // By controls engineering in frc,
  // x-dot = [0 1 | 0 -kv/ka] x = [0 | 1/ka] u
  double kv = 1.0;
  double ka = 0.5;
  auto model = frc::LinearSystemId::IdentifyPositionSystem<units::meter>(
      kv * 1_V / 1_mps, ka * 1_V / 1_mps_sq);

  ASSERT_TRUE(model.A().isApprox(
      Eigen::Matrix<double, 2, 2>{{0.0, 1.0}, {0.0, -kv / ka}}, 0.001));
  ASSERT_TRUE(
      model.B().isApprox(Eigen::Matrix<double, 2, 1>{0.0, 1.0 / ka}, 0.001));
}

TEST(LinearSystemIDTest, IdentifyVelocitySystem) {
  // By controls engineering in frc,
  // V = kv * velocity + ka * acceleration
  // x-dot =  -kv/ka * v + 1/ka \cdot V
  double kv = 1.0;
  double ka = 0.5;
  auto model = frc::LinearSystemId::IdentifyVelocitySystem<units::meter>(
      kv * 1_V / 1_mps, ka * 1_V / 1_mps_sq);

  ASSERT_TRUE(model.A().isApprox(Eigen::Matrix<double, 1, 1>{-kv / ka}, 0.001));
  ASSERT_TRUE(model.B().isApprox(Eigen::Matrix<double, 1, 1>{1.0 / ka}, 0.001));
}

// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "frc/AnalogAccelerometer.h"
#include "frc/PIDSource.h"

namespace frc {

/**
 * Wrapper so that PIDSource is implemented for AnalogAccelerometer for old
 * PIDController
 */
class PIDAnalogAccelerometer : public PIDSource, public AnalogAccelerometer {
  using AnalogAccelerometer::AnalogAccelerometer;

 public:
  /**
   * Get the Acceleration for the PID Source parent.
   *
   * @return The current acceleration in Gs.
   */
  double PIDGet() override;
};

}  // namespace frc

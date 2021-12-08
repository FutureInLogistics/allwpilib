// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <assert.h>

namespace frc {
/**
 * A class that implements an filter with an exponential decaying error.  
 * Useful for reducing measurement noise, while new values having the biggest impact.
 */
template <typename T>
class ExponentialFilter {

 public:
  /**
   * Creates a new ExponentialFilter.
   *
   * @param alpha The number of samples in the moving window.
   *    determining from [0,1] to which ratio the new value will be used.
   *    This makes it the smoothing factor with 1 being no smoothing at all.
   *    with 
   *        alpha = dT / tau, for dT << tau
   *    where
   *        dT = sampling time
   *        tau = time constant to reach 63% of the step function
   */
  explicit ExponentialFilter(double alpha) : 
    m_old_value(),
    m_inital_value(),
    m_alpha(alpha) // Take care that this initializer list in in the same order as the members
  {
    assert(alpha > 0);
    assert(alpha <= 1);

  }

  /**
   * Calculates the moving-window median for the next value of the input stream.
   *
   * @param next The next input value.
   * @return The median of the moving window, updated to include the next value.
   */
  T Calculate(T next) {
    m_old_value = m_alpha * next + (1-m_alpha) * m_old_value;
    return m_old_value;
  }

  /**
   * Resets the filter, clearing the window of all elements.
   */
  void Reset() { 
    m_old_value = m_inital_value;
  }

  /**
   * Sets the initial value for the filter.
   * @param v The initial value for the filter to start smoothing with.
   */
  void setInitialValue(const T& v) {
    m_inital_value = v;
  }

  T getCurrentValue() {
    return m_old_value;
  }

  void setAlpha(double alpha) { 
    m_alpha = alpha; 
  }

  double getAlpha() {
    return m_alpha;
  }

 private:
  T m_old_value;
  T m_inital_value;
  double m_alpha;

};
}  // namespace frc

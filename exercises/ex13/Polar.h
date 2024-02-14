/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include "Coordinate.h" //
#include <string>       // std::string

class Polar : public Coordinate {
 public:
  Polar();                                // Default constructor
  Polar(const double x, const double y);  // Overloaded constructor
  virtual ~Polar() { }                    // Deconstructor

  std::string ToString() const override;

  double Distance(const Polar &other) const;

 private:
  double r_, a_;
};  // class Polar
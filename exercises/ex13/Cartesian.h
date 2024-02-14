/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include "Coordinate.h" // Base class
#include <string>       // std::string

#ifndef CARTESIAN_H_
#define CARTESIAN_H_

class Cartesian : public Coordinate{
 public:
  Cartesian();                                // Default constructor
  Cartesian(const double x, const double y);  // Overloaded constructor
  virtual ~Cartesian() { }                    // Deconstructor

  std::string ToString() const override;

  double Distance(const Cartesian &other) const;

 private:
  double x_, y_;
};  // class Cartesian

#endif  // CARTESIAN_H_

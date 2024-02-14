/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include "Cartesian.h"  // Class header
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <cmath>        // std::sqrt()


Cartesian::Cartesian() : x_(0.0), y_(0.0) { }         // Default constructor
Cartesian::Cartesian(const double x, const double y)  // Overloaded constructor
                     : x_(x), y_(y) { }

// Returns the string representation of the object
std::string Cartesian::ToString() const { 
  std::stringstream ss;
  ss << '(' << x_ << ", " << y_<< ')';
  return ss.str();
}

// Calculates the distance between this and other using the Pythagorean theorem
double Cartesian::Distance(const Cartesian &other) const {
  long double x = this->x_ - other.x_;
  long double y = this->y_ - other.y_;
  x *= x;
  y *= y;
  long double total = x + y;
  return static_cast<double>(std::sqrt(total));
}

/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include "Polar.h" // class header
#include <string>  // std::string
#include <sstream> // std::stringstream
#include <cmath>  // std::pow(), std::sqrt()

#include <iostream>

Polar::Polar() : r_(0.0), a_(0.0) { } // Default constructor
Polar::Polar(const double radius,     // Overloaded constructor
             const double angle)
             : r_(radius), a_(angle) { }

// Returns the string representation of the object
std::string Polar::ToString() const { 
  std::stringstream ss;
  ss << '(' << this->r_ << ", " << this->a_<< "°)";
  return ss.str();
}

// Calculates the distance between this and other using the Pythagorean theorem
double Polar::Distance(const Polar &other) const {
  long double r = std::pow(this->r_, 2) + std::pow(other.r_, 2);
  long double cos = std::cos((other.a_ - this->a_) * M_PI / 180);
  return static_cast<double>(std::sqrt(r - (2 * this->r_ * other.r_ * cos)));
}
/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <iostream>  // for istream, ostream

#ifndef EX9_VECTOR_H_
#define EX9_VECTOR_H_

namespace vector333 {

class Vector {
 public:
  Vector();                       // Default constructor
  Vector(const double x,          // Overloaded constructor
          const double y,
          const double z);
  Vector(const Vector& other);    // Copy constructor
  ~Vector();                      // Destructor

  // Accessor inline member functions
  double get_x() const { return x_; }
  double get_y() const { return y_; }
  double get_z() const { return z_; }

  // Overloaded assignment operators
  Vector operator=(const Vector &a);
  Vector operator+=(const Vector &a);
  Vector operator-=(const Vector &a);

 private:
  double x_, y_, z_;
};  // class Vector

// Additional overloaded operators
Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);

double operator*(const Vector &a, const Vector &b);  // dot product
Vector operator*(const Vector &a, const double k);  // scalar multiplication

std::ostream &operator<<(std::ostream &out, const Vector &a);

}  // namespace vector333

#endif  // EX9_VECTOR_H_

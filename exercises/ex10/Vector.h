/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * 
 * ahansen4@uw.edu
 */

#ifndef EX10_VECTOR_H_
#define EX10_VECTOR_H_

#include <iostream>
using std::ostream;

namespace vector333 {

// A Vector represents a vector in 3-space.
class Vector {
 public:
  // constructors:

  // Default: construct the vector (0,0,0)
  Vector()
    : fields_(new double[3]{0.0, 0.0, 0.0}) {}

  // Construct the vector (x,y,z)
  Vector(const double x, const double y, const double z)
    : fields_(new double[3]{x, y, z}) { }

  // Copy constructor
  Vector(const Vector &v)
    : fields_(new double[3]{v.fields_[0], v.fields_[1], v.fields_[2]}) { }

  // Destructor - nothing to do
  ~Vector() {
    delete[] fields_;
  }

  // Assignment
  Vector &operator=(const Vector &rhs);

  // Updating assignment
  Vector &operator+=(const Vector &rhs);
  Vector &operator-=(const Vector &rhs);

  // dot-product: if a is (a,b,c) and b is (x,y,z),
  // return ax+by+cz
  friend double operator*(const Vector &a, const Vector &b);

  // scalar multiplication: if v is (a,b,c), return (ak,bk,ck)
  friend Vector operator*(const double k, const Vector &v);
  friend Vector operator*(const Vector &v, const double k);

  // Stream output: define << for Vectors
  friend ostream & operator<<(ostream &out, const Vector &v);

 private:
  // The representation of a Vector is three doubles giving
  // the x, y, and z magnitudes.
  double* fields_;
};

// additional operations that are not Vector class members
// but are part of the Vector abstraction

// addition and subtraction: produce a new Vector that results from
// element-wise addition or subtraction of a and b
Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);





}  // namespace vector333

#endif  //  EX10_VECTOR_H_

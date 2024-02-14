/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * Modified from Hal Perkins' exercise 9 sample solution.
 * 
 * ahansen4@uw.edu
 */

#include "Vector.h"

#include <iostream>
using std::ostream;

namespace vector333 {

// Vector assignment
Vector &Vector::operator=(const Vector &rhs) {
  // replace state of this with values from rhs; do nothing if
  // self-asignment. (Even though in this particular case there would
  // be no harm, it's always best to check for self-assignment and do
  // nothing if detected.)
  if (this != &rhs) {
    fields_[0] = rhs.fields_[0];
    fields_[1] = rhs.fields_[1];
    fields_[2] = rhs.fields_[2];
  }
  // return reference to lhs of assignment
  return *this;
}

// Updating assignments for vectors

Vector &Vector::operator+=(const Vector &rhs) {
  fields_[0] += rhs.fields_[0];
  fields_[1] += rhs.fields_[1];
  fields_[2] += rhs.fields_[2];
  return *this;
}

Vector &Vector::operator-=(const Vector &rhs) {
  fields_[0] -= rhs.fields_[0];
  fields_[1] -= rhs.fields_[1];
  fields_[2] -= rhs.fields_[2];
  return *this;
}

// Additional non-member functions that are part of the Vector absraction

// Vector addition
Vector operator+(const Vector &a, const Vector &b) {
  Vector tmp = a;
  tmp += b;
  return tmp;
}

// Vector subtraction
Vector operator-(const Vector &a, const Vector &b) {
  Vector tmp = a;
  tmp -= b;
  return tmp;
}

// dot-product: if a is (a,b,c) and b is (x,y,z),
// return ax+by+cz
double operator*(const Vector &a, const Vector &b) {
  return a.fields_[0]*b.fields_[0] +
         a.fields_[1]*b.fields_[1] + a.fields_[2]*b.fields_[2];
}

// scalar multiplication: if v is (a,b,c), return (ak,bk,ck)
Vector operator*(const double k, const Vector &v) {
  return Vector(v.fields_[0] * k, v.fields_[1] * k, v.fields_[2] * k);
}
Vector operator*(const Vector &v, const double k) {
  return Vector(v.fields_[0] * k, v.fields_[1] * k, v.fields_[2] * k);
}

// Stream output: << for Vectors
ostream & operator<<(ostream &out, const Vector &v) {
  out << "(" << v.fields_[0] << "," << v.fields_[1]
             << "," << v.fields_[2] << ")";
  return out;
}

}  // namespace vector333

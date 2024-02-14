/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include "Vector.h"
#include <iostream>  // printing statements

namespace vector333 {

  Vector::Vector() : x_(0.0), y_(0.0), z_(0.0) {}

  Vector::Vector(const double x, const double y, const double z) :
                 x_(x), y_(y), z_(z) {}

  Vector::Vector(const Vector& other) {
    this->x_ = other.x_;
    this->y_ = other.y_;
    this->z_ = other.z_;
  }

  Vector::~Vector() {}

  Vector Vector::operator=(const Vector &a) {
    // std::cout << "operator=: " << *this << " = " << a << std::endl;
    if (this != &a) {
      this->x_ = a.x_;
      this->y_ = a.y_;
      this->z_ = a.z_;
    }
    return *this;
  }

  Vector Vector::operator+=(const Vector &a) {
    if (this != &a) {
      this->x_ += a.x_;
      this->y_ += a.y_;
      this->z_ += a.z_;
    }
    return *this;
  }

  Vector Vector::operator-=(const Vector &a) {
    if (this != &a) {
      this->x_ -= a.x_;
      this->y_ -= a.y_;
      this->z_ -= a.z_;
    }
    return *this;
  }

  // Additional overloaded operators

  Vector operator+(const Vector &a, const Vector &b) {
    Vector tmp = a;
    tmp += b;
    return tmp;
  }

  Vector operator-(const Vector &a, const Vector &b) {
    Vector tmp = a;
    tmp -= b;
    return tmp;
  }

  double operator*(const Vector &a, const Vector &b) {
    double res = (
      a.get_x() * b.get_x() +
      a.get_y() * b.get_y() +
      a.get_z() * b.get_z());
    return res;
  }

  Vector operator*(const Vector &a, double k) {
    Vector tmp(
      a.get_x() * k,
      a.get_y() * k,
      a.get_z() * k);
    return tmp;
  }

  std::ostream &operator<<(std::ostream &out, const Vector &a) {
    out << "(" << a.get_x() << " , " << a.get_y() << " , " << a.get_z() << ")";
    return out;
  }
}  // namespace vector333

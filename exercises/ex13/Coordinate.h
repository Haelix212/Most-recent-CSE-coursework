/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <string>   // std::string

#ifndef COORDINATE_H_
#define COORDINATE_H_

class Coordinate {
 public:
  Coordinate() { }            // Default constructor
  virtual ~Coordinate() { }   // Destuctor

  virtual std::string ToString() const = 0;  
};  // class Coordinate

#endif  // COORDINATE_H_

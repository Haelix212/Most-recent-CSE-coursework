/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <cstdlib>      // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>     // std::cout, std::cin
#include <string>       // std::string
#include "Coordinate.h" //
#include "Cartesian.h"  //
#include "Polar.h"      //

using std::cout;
using std::endl;

int main(int argc, char** argv) {
  Cartesian zero = Cartesian();
  cout << "zero: " << zero.ToString() << endl;

  Cartesian one(1, 1);
  cout << "one: " << one.ToString() << endl;

  // Should be 1.41421
  cout << "Distance from zero to one: " << zero.Distance(one) << endl;
  cout << "Distance from one to zero: " << one.Distance(zero) << endl;

  Cartesian two(-147, 0.004);
  Cartesian three( 0.6, -10234);
  cout << "two: " << two.ToString() << endl;
  cout << "three: " << three.ToString() << endl;

  // Should be 10235.1
  cout << "Distance from two to three: " << two.Distance(three) << endl;
  cout << "Distance from three to two: " << three.Distance(two) << endl;
  cout << endl;

  Polar ten = Polar();
  cout << "ten: " << ten.ToString() << endl;

  Polar eleven(1, 45);
  cout << "eleven: " << eleven.ToString() << endl;

  // Should be 1
  cout << "Distance from ten to eleven: " << ten.Distance(eleven) << endl;
  cout << "Distance from eleven to ten: " << eleven.Distance(ten) << endl;

  Polar twelve(36.4, 135);
  Polar thirteen(-13, 100);
  cout << "twelve: " << twelve.ToString() << endl;
  cout << "thirteen: " << thirteen.ToString() << endl;

  // Should be 47.6362
  cout << "Distance from twelve to thirteen: " << twelve.Distance(thirteen) << endl;
  cout << "Distance from thirteen to twelve: " << thirteen.Distance(twelve) << endl;

  return EXIT_SUCCESS;
}
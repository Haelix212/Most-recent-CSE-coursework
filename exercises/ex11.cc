/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <cstdlib>    // EXIT_FAILURE/EXIT_SUCCESS
#include <iostream>   // std::cin/std::cout/std::endl
#include <vector>     // std::vector
#include <algorithm>  // std::sort

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::vector;
using std::sort;

template <class T> static T ReadValue(istream& in);

int main(int argc, char** argv) {
  int i;
  double num;
  vector<double> nums;

  cout << "Enter 6 doubles:" << endl;
  for (i = 0; i < 6; i++) {
    num = ReadValue<double>(cin);
    nums.push_back(num);
  }

  sort(nums.begin(), nums.begin() + 6);
  cout << "Your sorted doubles are:" << endl;
  for (i = 0; i < 6; i++) {
    cout << nums[i] << endl;
  }
  return EXIT_SUCCESS;
}

template <class T>
static T ReadValue(istream& in) {
  T input;
  in >> input;
  if (in.good()) {
    return input;
  } else {
    cout << "Not a double, shutting down..." << endl;
    exit(EXIT_FAILURE);
  }
}

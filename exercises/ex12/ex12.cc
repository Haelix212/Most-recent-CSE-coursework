/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <cstdlib>    // EXIT_FAILURE/EXIT_SUCCESS
#include <iostream>   // std::cin/std::cout/std::endl
#include <fstream>    // std::ifstream
#include <string>     // std::string
#include <map>        // std::map
#include <algorithm>  // for_each()

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Helper function to print a given map pair using for_each
static void Print(const std::pair<string, int> pair);


int main(int argc, char** argv) {
  std::ifstream input;
  std::string word;
  std::map<string, int> words;

  if (argc < 2) {
    cout << "Missing file name input" << endl;
    return EXIT_FAILURE;
  }

  input.open(argv[1], std::ios::in);
  if (input.is_open()) {
    while (input.good()) {
      input >> word;
      words[word]++;
    }
    input.close();

  } else {
    cout << "File '"<< argv[1] << "' could not be opened" << endl;
    return EXIT_FAILURE;
  }

  std::for_each(words.cbegin(), words.cend(), Print);
  return EXIT_SUCCESS;
}

////////////////////////////// Helper Functions ///////////////////////////////

static void Print(const std::pair<string, int> pair) {
  cout << pair.first << " " << pair.second << endl;
}

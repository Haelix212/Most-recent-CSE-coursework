/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#ifndef EX4_NTHPRIME_H_
#define EX4_NTHPRIME_H_

#include <inttypes.h>   // for special printing of specified variables

// Calculates and returns the nth prime number.
//
// Function has only been tested to be accurate as far as n = 100,
// results past that may vary in accuracy.
//
// Arguments:
// - n: the desired prime number in the sequence from 0.
//
// Returns:
// - the nth prime number.
int64_t NthPrime(int16_t n);

#endif  // EX4_NTHPRIME_H_

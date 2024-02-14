/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <stdio.h>      // for input/output
#include <stdint.h>     // for specified variable sizes
#include <inttypes.h>   // for special printing of specified variables
#include <stdlib.h>     // for EXIT_SUCCESS, EXIT_FAILURE
#include <stdbool.h>    // for bool type

// helper function to calculate if a number is prime
bool isPrime(int64_t);

int64_t NthPrime(int16_t n) {
    int64_t result = 2;

    // check for valid input
    if (n < 1) {
        printf("Invalid input\n");
        return -1;
    }

    for (int i = 1; i < n; i++) {
        result++;
        while (!(isPrime(result))) {
            result++;
        }
    }
    return result;
}

bool isPrime(int64_t n) {
    int list[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    int len = 12;
    int i;
    for (i = 0; i < len; i++) {
        if (n == list[i]) {
            return true;
        }
    }
    // n must be bigger than the largest value in list[], check for factors
    for (i = 0; i< len; i++) {
        if (n%list[i] == 0) {
            return false;
        }
    }
    return true;
}

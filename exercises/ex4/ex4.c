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
#include "NthPrime.h"   // for NthPrime

#define NUM_PRIMES 100

int main(int c, char* argv[]) {
    // big test of 1 to NUM_PRIMES values of n
    for (uint16_t i = 1; i < NUM_PRIMES+1; i++) {
        printf("Test %d, input: n = %d\n", i, i);
        if ((i > 20 || i == 1) && i%10 == 1) {
            printf("The %dst ", i);
        } else if ((i > 20 || i == 2) && i%10 == 2) {
            printf("The %dnd ", i);
        } else if ((i > 20 || i == 3) && i%10 == 3) {
            printf("The %drd ", i);
        } else {
            printf("The %dth ", i);
        }
        printf("prime number is: %ld\n", NthPrime(i));
    }
    return EXIT_SUCCESS;
}

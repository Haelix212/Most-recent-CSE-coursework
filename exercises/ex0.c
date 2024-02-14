// Alex Hansen
// ahansen4@uw.edu
// 1/4/2024
//
// This program takes an integer input "n" for the number of values of the Nilakantha series to use
// in approximatation of the value of Pi.
//
// Given no input parameter the function will prompt for an input value.
//
// All paramters after the first will be ignored.
//
// Non-integer inputs have no guarantee of being read correctly and may result in the approximate 
// value of Pi being 3.0. 
//
// Excessively large input values may take time to process.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    double pi, next;
    int n, i;

    if (argc < 2) { // no input
        printf("Please provide valid input \n");
        return 1;
    }

    n = atoi(argv[1]); // reads the first input parameter
    i = 1;
    pi = 3.0;

    while (i <= n) {
        next = (4.0/(2*i*(2*i+1)*(2*i+2))); // compute next value of the Nilakantha series
        if (i%2 == 0) { // the series alternates addition and subtraction 
            pi -= next;
        } else {
            pi += next;
        }
        i++;
    }
    
    printf("Our estimate of Pi is %.20f \n", pi); // print stored Pi to 20 decimal places
    return 0;
}
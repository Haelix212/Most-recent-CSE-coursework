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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide an input\n");
        return EXIT_FAILURE;
    }

    FILE* input;
    int size;
    char* name;
    char buffer[1];

    // process input name from argv[]
    name = argv[1];
    input = fopen(name, "rb");
    if (input == NULL) {
        printf("Please provide a valid file name\n");
        return EXIT_FAILURE;
    }

    // Get the size of the input file.
    fseek(input, 0, SEEK_END);
    size = ftell(input);

    // Move through the file backwards, printing each character.
    for (int i = size; i >= 0; i--) {
        fseek(input, i, SEEK_SET);
        fread(buffer, 1, 1, input);
        printf("%c", buffer[0]);
    }

    fclose(input);
    return EXIT_SUCCESS;
}

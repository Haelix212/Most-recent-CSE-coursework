// Alex Hansen
// ahansen4@uw.edu
// 1/11/2024

#include <stdio.h>      // for input/output
#include <stdint.h>     // for specified variable sizes
#include <inttypes.h>   // for special printing of specified variables
#include <stdlib.h>     // for EXIT_SUCCESS, EXIT_FAILURE

// define Point3d
typedef struct Point3d_str {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} Point3d, *Point3d_ptr;

// define AllocatePoint3d
Point3d_ptr AllocatePoint3d(uint16_t, uint16_t, uint16_t);

int main(int argc, char* argv[]) {
    uint16_t x, y, z;
    Point3d_ptr point;
    int success = 1;

    // set test input values
    x = 10;
    y = 15;
    z = 2;

    // allocate and confirm the new point
    point = AllocatePoint3d(x, y, z);
    if(point == NULL) {
        return EXIT_FAILURE;
    }

    // confirm allocation was successful
    if (point->x != x) {
        printf("Incorrect x value\n");
        success = 0;
    }
    if (point->y != y) {
        printf("Incorrect y value\n");
        success = 0;
    }
    if (point->z != z) {
        printf("Incorrect z value\n");
        success = 0;
    }

    // exit the program
    if (success == 1) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

Point3d_ptr AllocatePoint3d(uint16_t x, uint16_t y, uint16_t z) {
    Point3d_ptr point;

    // allocate and confirm new struct
    point = (Point3d_ptr) malloc(sizeof(Point3d));
    if(point == NULL) {
        printf("malloc failed");
        return NULL;
    }

    // assign inputs to correct fields
    point->x = x;
    point->y = y;
    point->z = z;

    // return the new struct pointer
    return point;
}
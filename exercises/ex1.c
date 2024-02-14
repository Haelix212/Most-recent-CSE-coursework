// Alex Hansen
// ahansen4@uw.edu
// 
// This program sorts a given array into a second array and then prints the sorted array to stdout.
// 
// Main is used to supply the test arrays and length values here.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int CopyAndSort(int64_t*, int64_t*, int);

int main(int argc, char* argv[]) {

    int64_t arr1[12] = {3, 2, -5, 7, 17, 42, 6, 333, 7, 8, -8, 6};
    // int64_t arr1[12] = {-8, -5, 2, 3, 6, 6, 7, 7, 8, 17, 42, 333};
    int64_t arr2[12];
    int length, res;

    length = 12;

    res = CopyAndSort(arr1, arr2, length);

    if (!res) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}


int CopyAndSort(int64_t arr1[], int64_t arr2[], int length) {
    int64_t item; 
    int sorted = 0;
    int i, j, k;

    // zero out values of arr2 for comparison purposes
    for (i = 0; i < length; i++) { 
        arr2[i] = 0;
    }    

    for (i = 0; i < length; i++) { // for every item in the first array
        item = arr1[i];

        for (j = 0; j < sorted; j++) { // check each sorted item against the new item
            
            if (arr2[j] > item) {               // if sorted item is larger than new item
                for (k = sorted; k >= j; k--) { // shift all larger items up by 1 index
                    arr2[k+1] = arr2[k];
                }
                arr2[j] = item;                 // insert item at its intended location
                break;                          // end the loop early
            }
        }
        if (j == sorted) { // if none of the sorted items are larger than the new item
            arr2[i] = item;
        }
        sorted++; // we've now sorted one more item
    }

    // print the sorted array
    for (i = 0; i < length; i++) {
        printf("%ld ", arr2[i]);
    }
    printf("\n");
    return 0;
}
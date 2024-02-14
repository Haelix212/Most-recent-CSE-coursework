// Alex Hansen
// ahansen4@uw.edu
// 1/8/2024

#include <stdio.h>      // for input/output
#include <stdint.h>     // for specified variable sizes
#include <inttypes.h>   // for special printing of specified variables
#include <stdlib.h>     // for EXIT_SUCCESS, EXIT_FAILURE


/* 
 * Takes input mem address and prints input number of bytes stored
 * starting from that address to stdout
*/
void PrintBytes(void* mem_addr, int num_bytes);

int main(int argc, char **argv) {
  char     char_val = '0';
  int32_t  int_val = 1;
  float    float_val = 1.0;
  double   double_val  = 1.0;

  typedef struct {
    char     char_val;
    int32_t  int_val;
    float    float_val;
    double   double_val;
  } Ex2Struct;

  Ex2Struct struct_val = { '0', 1, 1.0, 1.0 };

  PrintBytes(&char_val, sizeof(char));
  PrintBytes(&int_val, sizeof(int32_t));
  PrintBytes(&float_val, sizeof(float));
  PrintBytes(&double_val, sizeof(double));
  PrintBytes(&struct_val, sizeof(struct_val));

  return EXIT_SUCCESS;
}

void PrintBytes(void* mem_addr, int num_bytes) {
    int i;
    uint8_t *ptr;

    // setting up the pretty part of the output
    printf("The %d bytes starting at %p are:", num_bytes, mem_addr);

    // converting mem_addr to an easily printable and iterable array of uint8_t
    ptr = mem_addr;

    // loop to print values bytes that mem_addr points to
    for (i = 0; i < num_bytes; i++) {
        printf(" %02" PRIx8 , ptr[i]);
    }

    // end the line and exit
    printf("\n");
}
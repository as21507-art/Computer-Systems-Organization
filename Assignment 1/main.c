#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "functions.h"

void print_binary32(unsigned int  value) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}


void print_binary16(unsigned int  value) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

int main(int argc, char *argv[]) 
{
    if(argc<2)
    {
        printf("Incorrect command fromat. Usage %s <float> \n",argv[0]);
        return -1;
    }

    float test = atof(argv[1]);

    char* binary = float_to_binary(test);
    // Task 1 Convert float to binary
    printf("Task 1: The IEEE 754 FP32 binary representation of %.2f is:\n%s\n\n",test, binary);

    
    //Task 2 switch sigificand and exponents 
    char* switched = switch_significand_exponent_string(binary);
    printf("Task 2: After switching the significand and exponent bits:\n%s\n",switched);


    //Task 3 Invert Bits
    char  *inverted = invert_bit_string(binary);
    printf("\nTask 3: After inverting the bits of %s:\n%s\n",binary,inverted);


    //Task 4 Extract the sign bit of a float
    unsigned int sign = get_sign(test);
    printf("\nTask 4: The sign bit of %.2f is:\n",test);
    print_binary32(sign);


    //Task 5 Extract the exponent of the float
    unsigned int exponent = get_exponent(test);
    printf("\nTask 5: The exponent bits of %.2f are:\n",test);
    print_binary32(exponent);

    //Task 6 Extract the significant bits
    unsigned int significand = get_significand(test);
    printf("\nTask 6: The significand bits of %.2f are:\n",test);
    print_binary32(significand);

    // Task 7 Switch the significant and exponent bits of float
    unsigned int switched_value = switch_significand_exponent(test);
    printf("\nTask 7: After switching the significand and exponent bits of %.2f:\n",test);
    print_binary32(switched_value);


    // Task 8 Invert/Flip the sign-bit
    unsigned int sign_flipped = flip_sign(test);
    printf("\nTask 8: After flipping the sign bit of %.2f:\n",test);
    print_binary32(sign_flipped);


    unsigned int fp32;
    memcpy(&fp32, &test, sizeof(fp32));

    unsigned short fp16 = reduce_FP32_to_FP16(fp32);
    // Task 9 Convert float 32 to foat16
    printf("\nTask 9: The IEEE 754 FP16 binary representation of %.2f is:\n",test);
    print_binary16(fp16);

    //delete the dynamically allocated memory
    free(binary);
    free(switched);
    free(inverted);
    return 0;
  }

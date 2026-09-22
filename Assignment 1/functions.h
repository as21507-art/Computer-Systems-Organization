// Please implement the required functions in this file
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 CS-UH 2010: Computer Systems Organization (Assignment 1)
 Author: Aashish Shrestha
 Date Created: 2026-09-18
 */

/* Helper Functions */

// Function: Creates and populates the string with all 0 entries
// Input: a reference to the string representing the floating point representation
// Ouput: None
char *zero_case()
{
    // Allocating memory for the string
    char *zero_string = malloc(33);

    // Populating the string with all zeros
    for (int i = 0; i < 32; i++)
    {
        zero_string[i] = '0';
    }

    // Adding the string terminator
    zero_string[32] = '\0';

    return zero_string;
}

// Function: Converts the expoenent into the string
void norm_exponent(int exponent, char **float_string)
{

    // Index of the string
    int i = 8;

    // Converting the exponent to binary
    while (i != 0)
    {

        if (exponent % 2 == 0)
        {
            *float_string[i] = '0';
        }
        else
        {
            *float_string[i] = '1';
        }

        // Updating indices and exponent for next iteratios
        exponent = exponent / 2;
        i--;
    }
}

// Functions: Handles the conversion of infinities
char *inf_case(bool positive)
{

    // Allocating memory for the string
    char *float_string = malloc(33);

    // Adding the sign bit
    if (positive)
    {
        float_string[0] = '0';
    }
    else
    {
        float_string[0] = '1';
    }

    // Representing the expoenent
    for (int i = 1; i < 9; i++)
    {
        float_string[i] = '1';
    }

    // Representing the significand
    for (int i = 9; i < 32; i++)
    {
        float_string[i] = '0';
    }

    // Adding the string terminator
    float_string[32] = '\0';

    return float_string;
}

// Function: Handles the denormalized case
char *denorm_case(float *value, bool positive)
{
    // Allocating memory for the string
    char *float_string = malloc(33);

    // Determining the most significant bit
    if (positive)
    {
        float_string[0] = '1';
    }
    else
    {
        float_string[0] = '0';
    }

    // Constructing the expoenent
    for (int i = 1; i < 9; i++)
    {
        float_string[i] = '0';
    }

    // Constructing the significand
    for (int i = 9; i < 32; i++)
    {
        if (*value >= 1.0)
        {
            float_string[i] = '1';
            *value = *value - 1;
        }
        else
        {
            float_string[i] = '0';
        }
        *value = *value * 2;
    }

    // Adding the string terminator
    float_string[32] = '\0';

    return float_string;
}

// Function: Handles the conversion of positive number to floating point representation

char *positive_case(float *value)
{
    // Converting to positive infinity
    if (*value == INFINITY)
    {
        return inf_case(true);
    }

    // Initializing the biased exponent
    unsigned int biased_exponent = 127;

    // Normalizing values less than 1
    if (*value < 1.0)
    {
        while (*value < 1.0)
        {
            *value = *value * 2;
            biased_exponent--;
            if (biased_exponent == 0)
            {
                return denorm_case(&value);
            }
        }
    }

    // Normalizing values more than 1
    else if (*value >= 2.0)
    {
        while (*value >= 2.0)
        {
            *value = *value / 2;
            biased_exponent++;
        }
    }

    // Following representation is for normalized numbers

    // Allocating memory for the string
    char *float_string = malloc(33);

    // Adding the sign bit
    float_string[0] = '0';

    // Convert the expoenent directly into string
    norm_exponent(biased_exponent, &float_string);

    // Ignore the leading 1
    *value = *value - 1;

    // Converting the significand
    for (int i = 9; i < 32; i++)
    {
        *value = *value * 2;
        if (*value >= 1.0)
        {
            float_string[i] = '1';
            *value = *value - 1;
        }
        else
        {
            float_string[i] = '0';
        }
    }

    return float_string;
}

// Function: Handles the conversion of positive number to floating point representation

char *negative_case(float *value)
{

    // Converting to negative infinity
    if (*value == -INFINITY)
    {
        return inf_case(false);
    }

    // Initializing the biased exponent
    unsigned int biased_exponent = 127;

    // Normalizing values less than 1
    if (*value > -1.0)
    {
        while (*value > -1.0)
        {
            *value = *value * 2;
            biased_exponent--;
            if (biased_exponent == 0)
            {
                return denorm_case();
            }
        }
    }

    // Normalizing values more than 1
    else if (*value <= -2.0)
    {
        while (*value <= -2.0)
        {
            *value = *value / 2;
            biased_exponent++;
        }
    }

    // Following representation is for normalized numbers

    // Allocating memory for the string
    char *float_string = malloc(33);

    // Adding the sign bit
    float_string[0] = '1';

    // Convert the expoenent directly into string
    norm_exponent(biased_exponent, &float_string);

    // Ignore the leading 1
    *value = *value + 1;

    // Converting the significand
    for (int i = 9; i < 32; i++)
    {
        *value = *value * 2;
        if (*value <= -1.0)
        {
            float_string[i] = '1';
            *value = *value + 1;
        }
        else
        {
            float_string[i] = '0';
        }
    }

    return float_string;
}

/* Task 1 */

// Function: Takes a floating-point number in decimal and converts it into the IEEE 754 floating-point representation using 32 bits
// Input: Takes a float value in base 10
// Outputs: A character pointer (string) representing the 32 bit floating-point number in IEEE 754 representation
char *float_to_binary(float value)
{
    // Checking special edge #1 (value = 0)
    if (value == 0.0)
        return zero_case();
    else
    {
        // Determining the sign of the number
        if (value > 0.0)
            return positive_case(&value);
        else
            return negative_case(&value);
    }
}

/* Task 2 */

// Function: Swaps the position of significand and the exponenet in the IEEE 754 representation of a floating-point number
// Input: char* storing the string representation of the 32 bit IEEE 754 floating-point number
// Output: char* storing the string representation of the 32 bit IEEE 754 floating
char *switch_significand_exponent(char *value)
{

    // Allocating memory for the new string
    char *new_value = malloc(33);

    // Copying the most significant bit (MSB) to the new value
    new_value[0] = value[0];

    // Copying the significand to the new value
    for (int i = 1; i < 24; i++)
    {
        new_value[i] = value[i + 8];
    }

    // Copying the exponent to the new value
    for (int i = 1; i < 9; i++)
    {
        new_value[i + 23] = value[i];
    }

    // Adding the string terminator
    new_value[32] = '/0';

    return new_value;
}

/* Task 3 */

// Function: Inverts the positions of MSB, exponent, significand to significand, expoenent, MSB
// Input: char* storing the string representation of the 32 bit IEEE 754 floating point representation
// Ouput: char* storing the string represetnation of the 32 bit IEEE 754 floating point representation
char *invert_bit_string(char *value)
{

    // Allocating memory for the new string
    char *new_value = malloc(33);

    // Copying the most significant bit (MSB) to the new value
    new_value[31] = value[0];

    // Copying the significand to the new value
    for (int i = 0; i < 23; i++)
    {
        new_value[i] = value[i + 9];
    }

    // Copying the exponent to the new value
    for (int i = 1; i < 9; i++)
    {
        new_value[i + 22] = value[i];
    }

    // Adding the string terminator
    new_value[32] = '/0';

    return new_value;
}

/* Task: 4 */

// Function: Converts value from float to unsigned int
unsigned int converter(float *value)
{

    // Convert the value to string
    char *temp = float_to_binary(*value);

    // Convert the string to unsigned int
    unsigned int converted_value;

    // Copying the string representation to unsigned int
    for (int i = 0; i < 32; i++)
    {
        converted_value = converted_value * 2;
        if (temp[i] == '1')
        {
            converted_value++;
        }
    }

    return converted_value;
}

// Function: Extracts the sign bit from a floating point number using bit manipulation
// Input: float storing the value
// Output: unsigned int storing the sign of the flaoting point number
unsigned int get_sign(float value)
{
    // Initialize the floating value as unsigned integer to perform bitwise operations
    unsigned int new_value = converter(&value);

    // Perform the logical operations to remove the expoenent and significand
    new_value = new_value >> 31;

    // Undo the operation to restore the position of the sign bit
    new_value = new_value << 31;

    return new_value;
}

/* Task: 5 */

// Function: Extracts the expoenent from a given floating point number using bit manipulation
// Input: float storing the value
// Output: unsigned int storing the biased exponent
unsigned int get_exponent(float value)
{
    // Initialize the floating value as unsigned integer to perform bitwise operations
    unsigned int new_value = converter(&value);

    // Perform the logical operations to remove the sign bit
    new_value = new_value << 1;

    // Perform another operation to remove the significand
    new_value = new_value >> 24;

    return new_value;
}

/* Task: 6 */

// Function: Extracts the significand from a given floating point number using bit manipulation
// Input: float storing the value
// Output: unsigned int storing the significand
unsigned int get_significand(float value)
{
    // Initialize the floating value as unsigned integer to perform bitwise operations
    unsigned int new_value = converter(&value);

    // Perform the logical operations to remove the sign bit and the exponent
    new_value = new_value << 9;

    // Undo the operation to restore the position of the significand
    new_value = new_value >> 9;

    return new_value;
}

/* Task: 7 */

// Function: Switches the position of the significand and the exponent using bit manipulation
// Input: float storing the value
// Output: unsigned int storing the value with the expoenents and significand switched
unsigned int switch_significand_exponent(float value)
{
    // Initialize the sign, exponent and significand as unsigned integers to perform bitwise operations
    unsigned int sign = get_sign(value);
    unsigned int exponent = get_exponent(value);
    unsigned int significand = get_significand(value);

    // Change the position of the significand
    significand << 8;

    // Perform the and operation to get the swapped value
    return (significand & exponent) & sign;
}

/* Task : 8 */

// Function: Flips the sign of the floating point number using bit manipulation
// Input: float storing the value
// Ouput: unsigned int storing the value with the sign bit flipped
unsigned int flip_sign(float value)
{
    // Initialize the floating value as unsigned integer to perform bitwise operations
    unsigned int new_value = converter(&value);
    unsigned int sign = get_sign(value);

    // Only the sign is inverted by XOR
    return sign ^ new_value;
}

/* Task 9: */

// Function: Reduces a given floating point representation from 32 bits to 16 bits
// Input: unsigned int storing the float representation in 32 bits
// Output: unsigned short storing the float representation in 16 bits
unsigned short reduce_F32_to_F16(unsigned int value)
{
}

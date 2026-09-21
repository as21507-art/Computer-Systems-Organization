// Please implement the required functions in this file
# include <math.h>

/*
 CS-UH 2010: Computer Systems Organization (Assignment 1)
 Author: Aashish Shrestha
 Date Created: 2026-09-18
 */


// Helper function that converts the 32 bit IEEE 754 representation of 0
// Input: float_string pointer that stores the 32 bit IEEE 754 representation
// Ouptut: Void
void zero_case(char** float_string){
    
    // Floating-point value: 00000000000000000000000000000000
    for(int i = 0; i < 32; i++){
        float_string[i] = '0';
    }
}


// Helper function that initializes the sign of the number
// Input: value pointer that stores the value to be checked, float_string pointer that stores the the 32 bit IEEE 754 representation and sign pointer
void sign_checker(float* value, char** float_string, short* sign){
    
    // MSB 0 to represent positive
    if (value < 0) {
        float_string[0] = '0';
        sign = 1;
    }
    
    //MSB 1 to represent negative
    else {
        float_string[0] = '1';
        sign = -1;
    }
}


// Helper function to normalize a given number
// Input: a value
void normalizer(float* value, int* exponent){
    
    // Converting the value to normalized form 1.xxx * 2^y
    // Values with magnitude 1 or greater
    if (value >= 1 || value <= - 1){
        
        // Reduce any integral part strictly greater than 1
        while (value >= 2 || value <= -2){
            value = value / 2;
            exponent++;
        }
    }
    
    // Values with magitude less than 1
    else{
        
        // Increase to create an integral part at least 1
        while (value < 1 || value > - 1){
            value = value * 2;
            expoenent--;
        }
    }
}


// Helper function that constructs the significand from the given fractional part
// Input: pointer to the fractional part, the string storing the 32 bit IEEE 754 floating-point representation and sign
// Output: a boolean that is true if the mantissa is all zeros, and false otherwise
bool significand_converter(float* value, char** float_string, short* sign){
    
    // Boolean to check if the significand was all zeros
    bool all_zeros = true;
    
    // Iterating through the number to determine the significand
    for(int i = 9; i < 32; i++){
        
        value = value * 2;
        
        // Corresponds to a 1 in floating-point representation
        if (value >= 1){
            value = value - sign;
            float_string[i] = '1';
            all_zeros = false;
        }
        
        // Corresponds to a 0 in floating-point representation
        else {
            float_string[i] = '0';
        }
    }
    
    return all_zeros;
}


// Helper function to convert the exponent to binary

// Ouput: a boolean that is true if the biased exponenet is between 1 and 254 inclusive
bool convert_exponent(char** float_string, int* exponent){
    
    // Normalized form case
    if (exponent < 255 && exponent > 0){
        
        // Converting biased exponenet directly to binary
        for(int i = 7; i > 0; i--){
            if (exponent % 2 == 0) float_string[i] = '0';
            else float_string[i] = '1';
            exponent = exponent / 2;
        }
        
    }
    
    // Denormalized form case
    else {
        
        
    }
}


// Function: Takes a floating-point number in decimal and converts it into the IEEE 754 floating-point representation using 32 bits
// Input: Takes a float value in base 10
// Outputs: A character pointer (string) representing the 32 bit floating-point number in IEEE 754 representation
char* float_to_binary(float value){
    
    // Initializing the character pointer to store the answer and allocating 32 + 1 bits
    char* float_string;
    float_string = malloc(33);
    
    // Initializing the string terminator
    float_string[32] = '\0';
    
    // Checking special edge #1 (value = 0)
    if (value == 0.0) zero_case(&float_string);
    
    else{
        
        // Determining the sign of the floating-point number
        // sign: Stores 1 for positive number and -1 for negative number
        short sign;
        sign_checker(&value, &float_string, &sign);
        
        // Cases for extremely small numbers
        if (value < pow(2, -126) || value > - pow(2, -126)){
            
            
        }
        
        // General cases where the number is greater than
        else {
            
            // Initializing the biased exponent
            int exponenet = 127;
            
            // Normalizing the value to the form 1.xxx * 2^y
            normalizer(&value, &exponent);
            
            // Ignore the leading 1 in 1.xxx * 2^y
            value = value - sign;
            
            // Converting the exponent
            if (convert_exponent(&float_string, &exponent)){
                
                // Converting the significand if the exponenet is not in special case
                significand_converter(&value, &float_string, &sign);
            }
    }
    
    return float_string;
}




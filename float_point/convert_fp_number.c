/* 
    Auther      : Heinz Samuelsson
    Date        : 2014-11-02
    File        : conv_float2dec.c
    Reference   : http://en.wikipedia.org/wiki/Single-precision_floating-point_format
    Description : Convert IEEE 754 single-precision binary floating-point 
                  format: binary32 to decimal value.

                  To check floating point number see:
                    http://babbage.cs.qc.cuny.edu/IEEE-754.old/Decimal.html

                  value = (-1)^sign * (1.b22 b21 b20 ... b0) * 2^(exp-127)
*/

#include <stdio.h>
#include <stdlib.h>  // malloc and free function
#include <string.h>  // strcpy function
#include <math.h>

#define IMPLICIT_BIT 1  // implicit bit


// struct holding the floating point format number
typedef struct {
    char  value32bit[32]; // all 32 bits of the floating point number
    int   sign;           // 1 bit, +1 or -1
    char  exponent[8];    // exponent, 8 bits
    char  mantissa[24];   // mantissa, 24 bits
} FloatPointNumber;


// global declaration used by all functions
static FloatPointNumber fpNumber;


// convert input decimal integer data to binary string
char* decimal2binary(int n) {

    int   d;
    int   count = 0;
    char* pointer;

    pointer = (char*)malloc(32);
    if (pointer == NULL)
        exit(EXIT_FAILURE);

    for (int c=7; c>=0; c--) {
        d = n >> c;
        if (d&1)
            *(pointer+count) = 1 + '0';
        else
            *(pointer+count) = 0 + '0';

        count++;
    }

    return pointer;
}


// convert array of data to a binary string
void convert_array(int* indata) {

    char* p_binvalue;
    char  bin_data[33];

    // 32 bits of data is created
    for (int i=0; i<4; i++) {
        p_binvalue = decimal2binary(indata[i]);

        for (int j=0; j<8; j++) {
            bin_data[j+i*8] = p_binvalue[j];
        }
    }

    bin_data[32] = '\n';
    for (int k=0; k<32; k++) {
    }

    strcpy(fpNumber.value32bit,bin_data);
}


// get sign bit of data
void get_sign(char* bin_data) {

    int   sign;

    if (*(bin_data) == '1') {
        sign = -1;
    }
    else {
        sign = 1;
    }

    fpNumber.sign = sign;
}


// get exponent
void get_exponent(char* indata) {

    char exponent[8];

    for (int k=1; k<9; k++) {
        exponent[k-1] = *(indata+k);
    }

    strcpy(fpNumber.exponent,exponent);
}


// get mantissa
void get_mantissa(char* indata) {

    char mantissa[23];

    for (int k=9; k<32; k++) {
        mantissa[k-9] = *(indata+k);
    }

    strcpy(fpNumber.mantissa,mantissa);
}


// convert the exponent to decimal number
int bin2dec(char* indata) {

    char chardata[8];
    strncpy(chardata,indata,8);

    int decimal_data = (int)strtol(chardata,NULL,2);
    return (decimal_data - 127);
}


// convert the mantissa to decimal number
int bin2dec2(char* indata) {

    char chardata[24];
    strncpy(chardata,indata,24);
    chardata[23] = '\n';

    int decimal_data = (int)strtol(chardata,NULL,2);

   return decimal_data;
}


// calculate 1/2^n
float power(int x) {

    int   p = 1;
    float q = 0.0;

    for (int i=0; i<x+1; i++) {
        p = p * 2;
        q = 1/(float)p;
    }
    return q;
}


// calculate 2^n
float power_of_2(int n) {

    float pow = 1.0;
    int   i   = 1;

    while (i <= abs(n)) {
        pow = (float)(pow * 2.0);
        i++;
    }

    if (n > 0)
        return pow;
    else
        return (float)(1.0/pow);
}


// calculate floating point value
float calc_floating_point_value(FloatPointNumber fpNo, int dec_exponent) {

    float sum;

    for (int i=0; i<23; i++) {
        if (fpNo.mantissa[i] == '1') {
            sum += power(i);
        }
    }

    float x = power_of_2(dec_exponent);
    float result = (float)fpNumber.sign*(IMPLICIT_BIT+sum) * x;
    
    return result;
}

#define ARR_SIZE 6


/* *** MAIN *** */
int main(void) {

    // define test data
    int indata[ARR_SIZE][4] = {
                                         {195,47,0,0},    // -175
                                         {67,7,0,0},      // -135
                                         {62,32,0,0},     // 0.156250
                                         {193,58,225,72}, // -11.68
                                         {64,73,15,216},  // 3.141592
                                         {70,210,240,0}   // 27000
                                        };

    printf("------------------------------\n");

    for (int testround=0; testround<ARR_SIZE; testround++) {

        convert_array(indata[testround]);
        get_sign(fpNumber.value32bit);
        get_exponent(fpNumber.value32bit);
        get_mantissa(fpNumber.value32bit);

        int dec_exponent = bin2dec(fpNumber.exponent);
        //int dec_mantissa = bin2dec2(fpNumber.mantissa);
        float rv = calc_floating_point_value(fpNumber,dec_exponent);

        printf("Result: %f\n",rv);
        printf("------------------------------\n");
    }

    return 0;
}

/* Result:
     ------------------------------
     Result: -175.000000
     ------------------------------
     Result: 135.000000
     ------------------------------
     Result: 0.156250
     ------------------------------
     Result: -11.680000
     ------------------------------
     Result: 3.141592
     ------------------------------
     Result: 27000.000000
     ------------------------------
*/



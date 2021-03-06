/* 
    Auther      : Heinz Samuelsson
    Date        : 2013-11-30
    File        : conv_float2dec2.c
    Reference   : sandbox.mc.edu/~bennet/cs110/flt/ftod.html
                  babbage.cs.qc.cuny.edu/IEEE-754.old/Decimal.html
    Description : Handle floating point conversion.

            To calculate the decimal value the following is used:
            value = (-1)^sign * (1.b22 b21 b20 ... b0) * 2^(exp-127)
*/

#include <stdio.h>
#include <stdlib.h>  // malloc and free function
#include <string.h>  // strcpy function
#include <math.h>

#define IMPLICIT_BIT 1  // implicit bit
#define BIAS_ON      1  // biased on, used to calculate exponent
#define BIAS_OFF     1  // biased off, used to calculate mantissa


// convert input decimal integer data to binary string
char* decimal2binary(int n) {

    int d;
    int count = 0;
    char* pointer;

    pointer = (char*)malloc(32+1);

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

    *(pointer+count) = '\0';
    return pointer;
}


// convert binary string to decimal
int bin2dec(int bias, char* data) {

    int decimal_data = (int)strtol(data,NULL,2);	

    if (bias == 1) 
        return (decimal_data - 127);
    else
        return decimal_data;
}


// calculate 1/2^n
float power(int x) {

    int p = 1;
    float q = 0.0;

    for (int i=0; i<x+1; i++) {
	p = p * 2;
	q = 1/(float)p;
     }

    return q;
}


// calculate 2^n
float power_of_2(int n) {

    int pow = 1;
    int i   = 1;

    while (i <= abs(n)) {
        pow = pow * 2;
	i++;
    }

    if (n > 0)
        return pow;
    else
        return 1.0/pow;
}


/* *** MAIN *** */
int main(void) {

    //char  indata[4] = {67,7,0,0};    // 135 => 0x43070000
    //char  indata[4] = {62,32,0,0};   // 0.15625 => 0x3e200000
    //char  indata[4] = {66,92,0,0};   // 55 => 0x425c0000
    //char  indata[4] = {63,128,0,0};  // 1 => 0x3f800000
    //char  indata[4] = {67,160,0,0};  // 320 => 0x43a00000
    //char  indata[4] = {195,47,0,0};  // -175 => 0xc32f0000
    char  indata[4] = {193,58,225,72};  // -11.68 => 0xc13ae148

    char* p_binvalue;
    char  bin_data[32];
    char  exponent[8];
    char  mantissa[23];
    float sum;
    int   sign;

    // convert decimal to binary
    for (int i=0; i<4; i++) {
        p_binvalue = decimal2binary(indata[i]);
        printf("Binary string of %d is: %s\n",indata[i],p_binvalue);
        
        // print out every bits
        for (int j=0; j<8; j++) {
	    bin_data[j+i*8] = p_binvalue[j];
        }
    }
    printf("\n");

    // make a 32 bit vector and print it out
    for (int k=0; k<32; k++) {
        printf("%c",*(bin_data+k));
	if (k == 7 || k==15 || k==23) { 
            printf("\n");
        }
    }
    printf("\n");

    // check if the number negative or positive (msb)
    if (*(bin_data) == '1') {
        printf("msb: %c -> ",*(bin_data));
        printf("Negative number\n");
	sign = -1;
    }
    else {
        printf("msb: %c -> ",*(bin_data));
        printf("Positive number\n");
	sign = 1;
    }

    // find exponent, 8 bits, and assign its variable
    printf("Exponent (bin): ");
    for (int k=1; k<9; k++) {
        printf("%c",*(bin_data+k));
	exponent[k-1] = *(bin_data+k);
    }
    printf("\n");

    // make sure end of line is the last chararcter
    exponent[8] = '\n';

    // convert the exponent
    int dec_exponent = bin2dec(BIAS_ON,exponent);
    printf("Exponent (dec): %d\n",dec_exponent);


    // find mantissa, 23 bits, and assign its variable
    printf("Mantissa (bin): ");
    for (int k=9; k<32; k++) {
        printf("%c",*(bin_data+k));
	mantissa[k-9] = *(bin_data+k);
    }
    printf("\n");

    // make sure end of line is the last chararcter
    exponent[23] = '\n';

    int dec_mantissa = bin2dec(BIAS_OFF,mantissa);
    printf("Mantissa (dec): %d\n",dec_mantissa);

    for (int i=0; i<23; i++) {
        if (mantissa[i] == '1') {
	    sum += power(i);
	}
     }
   
    // remember to add implicit leading bit
    printf("sum: %.10f\n",IMPLICIT_BIT+sum);

    float x = power_of_2(dec_exponent);
    printf("x: %f\n",x);    

    printf("------------------------------\n");
    float result = sign*(IMPLICIT_BIT+sum) * x;
    printf("Result: %f\n",result);
    printf("------------------------------\n");

    free(p_binvalue);

    return 0;
}


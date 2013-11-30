/* 
    Auther      : Heinz Samuelsson
    Date        : 2013-11-30
    File        : conv_float2dec.c
    Reference   : -
    Description : Convert floating pointer value to decimal value.
*/

#include <stdio.h>
#include <stdlib.h>  // malloc and free function
#include <string.h>  // strcpy function

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


/* *** MAIN *** */
int main(void) {

    char indata[4] = {163,53,128,0};
    int  sign = 0;
    char* p_binvalue;

    for (int i=0; i<4; i++) {
        printf("dec - indata[%i]: %d\n",i,indata[i]);
        printf("hex - indata[%i]: %02x\n\n",i,indata[i]);
    }

    // check if value is negative
    if (indata[0] > 127) {
	sign = 1;
        printf("Value is negative. %d\n",sign);
    }

    // convert decimal to binary
    for (int j=0; j<4; j++) {
        p_binvalue = decimal2binary(indata[j]);
        printf("Binary string of %d is: %s\n",indata[j],p_binvalue);
        
        // print out every bits
        for (int i=0; i<8; i++) {
            printf("Bit[%d]: %c\n",i,p_binvalue[i]);
        }
    }

    free(p_binvalue);

    return 0;
}


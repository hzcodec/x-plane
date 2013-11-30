/* 
    Auther      : Heinz Samuelsson
    Date        : 2013-11-30
    File        : conv_float2dec.c
    Reference   : -
    Description : Print out binary digits from decimal value.
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
    char* p_binvalue;
    char bin_data[32];

    // convert decimal to binary
    for (int j=0; j<4; j++) {
        p_binvalue = decimal2binary(indata[j]);
        printf("Binary string of %d is: %s\n",indata[j],p_binvalue);
        
        // print out every bits
        for (int i=0; i<8; i++) {
	    bin_data[i+j*8] = p_binvalue[i];
        }
    }

    // make a 32 bit vector and print it out
    for (int k=0; k<32; k++) {
        printf("%c",*(bin_data+k));
	if (k == 7 || k==15 || k==23) { 
            printf("\n");
        }
    }
    printf("\n");

    free(p_binvalue);

    return 0;
}


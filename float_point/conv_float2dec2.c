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
#include <math.h>

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
int bin2dec(char* data) {

    int decimal_data = (int)strtol(data,NULL,2);	
    return (decimal_data - 127);
}

// convert binary string to decimal
int bin2dec2(char* data) {

    int decimal_data = (int)strtol(data,NULL,2);	
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


/* *** MAIN *** */
int main(void) {

    char  indata[4] = {163,53,128,0};
    char* p_binvalue;
    char  bin_data[32];
    char  exponent[8];
    char  mantissa[23];
    float sum;

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
    }
    else {
        printf("msb: %c -> ",*(bin_data));
        printf("Positive number\n");
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

    int x = bin2dec(exponent);
    printf("Exponent (dec): %d\n",x);


    // find mantissa, 23 bits, and assign its variable
    printf("Mantissa (bin): ");
    for (int k=9; k<32; k++) {
        printf("%c",*(bin_data+k));
	mantissa[k-9] = *(bin_data+k);
    }
    printf("\n");

    // make sure end of line is the last chararcter
    exponent[23] = '\n';

    int y = bin2dec2(mantissa);
    printf("Mantissa (dec): %d\n",y);

    for (int i=0; i<23; i++) {
        if (mantissa[i] == '1') {
	    sum += power(i);
//	    printf("summa %f\n",sum);
	}
     }
   
    printf("sum: %.10f\n",1+sum);

    free(p_binvalue);

    return 0;
}


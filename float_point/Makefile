CC     = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall

f1: conv_float2dec.c
	$(CC) $(CFLAGS) conv_float2dec.c -o conv_float2dec

f2: conv_float2dec2.c
	$(CC) $(CFLAGS) conv_float2dec2.c -o conv_float2dec2

f3: convert_fp_number.c
	$(CC) $(CFLAGS) -Wconversion convert_fp_number.c -o convert


clean:
	rm -f a.out conv_float2dec conv_float2dec2 convert

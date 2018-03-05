#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int	main(void)
{
	// char			*str = "The quick brown fox jumps over the lazy dog";
	char			*str = "The quick brown fox jumps over the lazy dog.";
	char			b512[64];
	unsigned int	a0 = 1732584193;
	unsigned int	b0 = 4023233417;
	unsigned int	c0 = 2562383102;
	unsigned int	d0 = 271733878;
	unsigned int	m[16];
	char			result[16];
	unsigned int	s[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
							  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
							  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
							  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};
	unsigned int	k[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
							 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
							 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
							 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
							 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
							 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
							 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
							 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
							 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
							 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
							 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
							 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
							 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
							 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
							 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
							 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	// Set the 512 block
	memset(b512, 0, 64);
	memcpy(b512, str, strlen(str));
	b512[strlen(str)] = 1 << 7;
	*(unsigned int*)(b512 + 56) = strlen(str) * 8 % UINT_MAX;
	*(unsigned int*)(b512 + 60) = strlen(str) * 8 / UINT_MAX;
	memset(result, 0, 16);

	// Print the 512 block
	write(1, b512, 64);
	write(1, "\n", 1);

	// Divise the 512 block in 16 blocks of 32 bits
	for (unsigned int i = 0; i < 16; i++)
	{
		printf("b512 %2hhx%2hhx%2hhx%2hhx  %2hhx%2hhx%2hhx%2hhx\n",
			*(b512 + i * 4), *(b512 + i * 4 + 1),
			*(b512 + i * 4 + 2), *(b512 + i * 4 + 3),
			*(b512 + i * 4 + 3), *(b512 + i * 4 + 2),
			*(b512 + i * 4 + 1), *(b512 + i * 4));
		m[i] = 0;
		m[i] |= *(b512 + i * 4) & 255;
		m[i] |= *(b512 + i * 4 + 1) << 8 & 65280;
		m[i] |= *(b512 + i * 4 + 2) << 16 & 16711680;
		m[i] |= *(b512 + i * 4 + 3) << 24 & 4278190080;
		// m[i] |= *(b512 + i * 4) + (*(b512 + i * 4 + 1) << 8) + (*(b512 + i * 4 + 2) << 16) + (*(b512 + i * 4 + 3) << 24);
		printf("m[%u] %8x  %u\n\n", i, m[i], m[i]);
		// memcpy(m[i], b512 + i * 4, 4);
	}

	// Loop for each 512 blocks but not here
	unsigned int a = a0;
    unsigned int b = b0;
    unsigned int c = c0;
    unsigned int d = d0;

	// Main loop
	for (unsigned int i = 0; i < 64; i++)
	{
		unsigned int f, g;
		if (i < 16)
		{
			f = (b & c) | ((~b) & d);
			g = i;
		}
		else if (i < 32)
		{
			f = (d & b) | ((~d) & c);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			f = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}
		else
		{
			f = c ^ (b | (~d));
			g = (7 * i) % 16;
		}
		f = f + a + k[i] + m[g];
		a = d;
		d = c;
		c = b;
		b = b + (f << s[i]);
		b = b + (f >> (32 - s[i]));
		printf("[%2u] %10u %10u %10u %10u\n", i, a, b, c, d);
	}

	// Inside the loop of each 512 block
	a0 += a;
	b0 += b;
	c0 += c;
	d0 += d;

	// Recompose the result
	// var char digest[16] := a0 append b0 append c0 append d0
	printf("A %8x\n", a0);
	printf("B %8x\n", b0);
	printf("C %8x\n", c0);
	printf("D %8x\n", d0);
	memcpy(result, &a0, 4);
	memcpy(result + 4, &b0, 4);
	memcpy(result + 8, &c0, 4);
	memcpy(result + 12, &d0, 4);

	// Print the result
	for (unsigned int i = 0; i < 16; i++)
		printf("%2hhx", result[i]);
	printf("\n");

	// Print the final result from wikipedia
	write(1, "e4d909c290d0fb1ca068ffaddf22cbd0\n", 33);
	write(1, "9e107d9d372bb6826bd81d3542a419d6\n", 33);
	return (0);
}

// var int a0 := 0x67452301   //A
// var int b0 := 0xefcdab89   //B
// var int c0 := 0x98badcfe   //C
// var int d0 := 0x10325476   //D

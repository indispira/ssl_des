#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

uint32_t rotr32 (unsigned int value, unsigned int count)
{
    const unsigned int mask = CHAR_BIT*sizeof(value) - 1;
    count &= mask;
    return (value >> count) | (value << (-count & mask));
}

void	switch_endianess(char *s)
{
	char	tmp[4];

	tmp[0] = s[3];
	tmp[1] = s[2];
	tmp[2] = s[1];
	tmp[3] = s[0];
	memcpy(s, tmp, 4);
}

int	main(void)
{
	// char			*str = "abc";
	// char			*str = "The quick brown fox jumps over the lazy dog";
	char			*str = "The quick brown fox jumps over the lazy dog.";
	char			b512[64];
	unsigned int	h0 = 0x6a09e667;
	unsigned int	h1 = 0xbb67ae85;
	unsigned int	h2 = 0x3c6ef372;
	unsigned int	h3 = 0xa54ff53a;
	unsigned int	h4 = 0x510e527f;
	unsigned int	h5 = 0x9b05688c;
	unsigned int	h6 = 0x1f83d9ab;
	unsigned int	h7 = 0x5be0cd19;
	unsigned int	m[64];
	char			result[32];
	unsigned int	s[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
							  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
							  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
							  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};
	unsigned int	k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
							 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
							 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
							 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
							 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
							 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
							 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
							 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
							 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
							 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
							 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
							 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
							 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
							 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
							 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
							 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

	// Set the 512 block with padding
	memset(b512, 0, 64);
	memcpy(b512, str, strlen(str));
	b512[strlen(str)] = 1 << 7;
	*(unsigned int*)(b512 + 60) = strlen(str) * 8 % UINT_MAX;
	*(unsigned int*)(b512 + 56) = strlen(str) * 8 / UINT_MAX;
	switch_endianess(b512 + 56);
	switch_endianess(b512 + 60);
	//*(unsigned int*)(b512 + 56) = strlen(str) * 8 % UINT_MAX;
	//*(unsigned int*)(b512 + 60) = strlen(str) * 8 / UINT_MAX;
	memset(result, 0, 16);

	// Print the 512 block
	write(1, "START\n", 6);
	write(1, b512, 64);
	write(1, "\n", 1);

	// Divise the 512 block in 16 blocks of 32 bits
	for (unsigned int i = 0; i < 16; i++)
	{
		printf("b512  %02hhx%02hhx%02hhx%02hhx  %02hhx%02hhx%02hhx%02hhx\n",
			*(b512 + i * 4), *(b512 + i * 4 + 1),
			*(b512 + i * 4 + 2), *(b512 + i * 4 + 3),
			*(b512 + i * 4 + 3), *(b512 + i * 4 + 2),
			*(b512 + i * 4 + 1), *(b512 + i * 4));
		m[i] = 0;
		m[i] |= *(b512 + i * 4 + 3) & 255;
		m[i] |= *(b512 + i * 4 + 2) << 8 & 65280;
		m[i] |= *(b512 + i * 4 + 1) << 16 & 16711680;
		m[i] |= *(b512 + i * 4 ) << 24 & 4278190080;
		//m[i] |= *(b512 + i * 4) & 255;
		//m[i] |= *(b512 + i * 4 + 1) << 8 & 65280;
		//m[i] |= *(b512 + i * 4 + 2) << 16 & 16711680;
		//m[i] |= *(b512 + i * 4 + 3) << 24 & 4278190080;
		printf("m[%2u] %08x  %u\n\n", i, m[i], m[i]);
	}

	// Loop for each 512 blocks but not here
	unsigned int a = h0;
    unsigned int b = h1;
    unsigned int c = h2;
    unsigned int d = h3;
    unsigned int e = h4;
    unsigned int f = h5;
    unsigned int g = h6;
    unsigned int h = h7;
    unsigned int s0, s1;

	// Main loop
	for (unsigned int i = 16; i < 64; i++)
	{
		s0 = (rotr32(m[i - 15], 7)) ^ (rotr32(m[i - 15], 18)) ^ (m[i - 15] >> 3);
		s1 = (rotr32(m[i - 2], 17)) ^ (rotr32(m[i - 2], 19)) ^ (m[i - 2] >> 10);
		m[i] = m[i - 16] + s0 + m[i - 7] + s1;
	}
	for (unsigned int i = 0; i < 64; i++)
	{
		unsigned int ch, ma, t1, t2;
		ch = (e & f) ^ ((~e) & g);
		ma = (a & b) ^ (a & c) ^ (b & c);
		s1 = rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25);
		s0 = rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22);
		// s0 = rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25);
		// s1 = rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22);
		t1 = h + s1 + ch + k[i] + m[i];
		t2 = s0 + ma;
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
		printf("%2u. %8x %8x %8x %8x %8x %8x %8x %8x\n",
			i, a, b, c, d, e, f, g, h);
	}

	// Inside the loop of each 512 block
	h0 += a;
	h1 += b;
	h2 += c;
	h3 += d;
	h4 += e;
	h5 += f;
	h6 += g;
	h7 += h;

	// Recompose the result
	printf("A %08x\n", h0);
	printf("B %08x\n", h1);
	printf("C %08x\n", h2);
	printf("D %08x\n", h3);
	printf("E %08x\n", h4);
	printf("F %08x\n", h5);
	printf("G %08x\n", h6);
	printf("H %08x\n", h7);
	memcpy(result, &h0, 4);
	memcpy(result + 4, &h1, 4);
	memcpy(result + 8, &h2, 4);
	memcpy(result + 12, &h3, 4);
	memcpy(result + 16, &h4, 4);
	memcpy(result + 20, &h5, 4);
	memcpy(result + 24, &h6, 4);
	memcpy(result + 28, &h7, 4);
	for (unsigned int i = 0; i < 32; i += 4)
		switch_endianess(result + i);

	// Print the result
	for (unsigned int i = 0; i < 32; i++)
		printf("%02hhx", result[i]);
	printf("\n");

	// Print the final result from wikipedia
	// write(1, "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad\n", 65);
	// write(1, "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592\n", 65);
	write(1, "ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c\n", 65);
	return (0);
}



// SHA-512 initial hash values (in big-endian):

// h[0..7] := 0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1, 
//            0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179

// SHA-512 round constants:

// k[0..79] := [ 0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 
//               0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 
//               0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 
//               0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 
//               0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 
//               0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 
//               0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 
//               0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 
//               0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 
//               0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 
//               0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 
//               0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 
//               0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 
//               0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 
//               0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 
//               0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817]

// SHA-512 Sum & Sigma:

// S0 := (a rightrotate 28) xor (a rightrotate 34) xor (a rightrotate 39)
// S1 := (e rightrotate 14) xor (e rightrotate 18) xor (e rightrotate 41)

// s0 := (w[i-15] rightrotate 1) xor (w[i-15] rightrotate 8) xor (w[i-15] rightshift 7)
// s1 := (w[i-2] rightrotate 19) xor (w[i-2] rightrotate 61) xor (w[i-2] rightshift 6)

// 5.1.  SHA-224 and SHA-256

//    SHA-224 and SHA-256 use six logical functions, where each function
//    operates on 32-bit words, which are represented as x, y, and z.  The
//    result of each function is a new 32-bit word.

//       CH( x, y, z) = (x AND y) XOR ( (NOT x) AND z)

//       MAJ( x, y, z) = (x AND y) XOR (x AND z) XOR (y AND z)

//       BSIG0(x) = ROTR^2(x) XOR ROTR^13(x) XOR ROTR^22(x)

//       BSIG1(x) = ROTR^6(x) XOR ROTR^11(x) XOR ROTR^25(x)

//       SSIG0(x) = ROTR^7(x) XOR ROTR^18(x) XOR SHR^3(x)

//       SSIG1(x) = ROTR^17(x) XOR ROTR^19(x) XOR SHR^10(x)

// 5.2.  SHA-384 and SHA-512

//    SHA-384 and SHA-512 each use six logical functions, where each
//    function operates on 64-bit words, which are represented as x, y, and
//    z.  The result of each function is a new 64-bit word.

//       CH( x, y, z) = (x AND y) XOR ( (NOT x) AND z)

//       MAJ( x, y, z) = (x AND y) XOR (x AND z) XOR (y AND z)

//       BSIG0(x) = ROTR^28(x) XOR ROTR^34(x) XOR ROTR^39(x)

//       BSIG1(x) = ROTR^14(x) XOR ROTR^18(x) XOR ROTR^41(x)

//       SSIG0(x) = ROTR^1(x) XOR ROTR^8(x) XOR SHR^7(x)

//       SSIG1(x) = ROTR^19(x) XOR ROTR^61(x) XOR SHR^6(x)

//    SHA-384 and SHA-512 use the same sequence of eighty constant 64-bit
//    words, K0, K1, ... K79.  These words represent the first 64 bits of
//    the fractional parts of the cube roots of the first eighty prime
//    numbers.  In hex, these constant words are as follows (from left to
//    right):

// uint32_t rotl32 (uint32_t value, unsigned int count) {
//     const unsigned int mask = CHAR_BIT*sizeof(value) - 1;
//     count &= mask;
//     return (value << count) | (value >> (-count & mask));
// }

// uint32_t rotr32 (uint32_t value, unsigned int count) {
//     const unsigned int mask = CHAR_BIT*sizeof(value) - 1;
//     count &= mask;
//     return (value >> count) | (value << (-count & mask));
// }

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

unsigned long rotr64b(unsigned long v, unsigned int nb)
{
	unsigned long	tmp;

	while (nb--)
	{
		tmp = v & 1;
		v = v >> 1;
		v += tmp;
	}
	return (v);
}

unsigned long rotr64 (unsigned long value, unsigned long count)
{
	const unsigned long mask = CHAR_BIT*sizeof(value) - 1;
	count &= mask;
	return (value >> count) | (value << (-count & mask));
}

void	switch_endianess(char *s)
{
	char	tmp[8];

	tmp[0] = s[7];
	tmp[1] = s[6];
	tmp[2] = s[5];
	tmp[3] = s[4];
	tmp[4] = s[3];
	tmp[5] = s[2];
	tmp[6] = s[1];
	tmp[7] = s[0];
	memcpy(s, tmp, 8);
}

int	main(void)
{
	char			*str = "abc";
	// char			*str = "The quick brown fox jumps over the lazy dog";
	// char			*str = "The quick brown fox jumps over the lazy dog.";
	char			b1024[128];
	unsigned long	m[64];
	char			result[64];
	unsigned long	h0 = 0x6a09e667f3bcc908;
	unsigned long	h1 = 0xbb67ae8584caa73b;
	unsigned long	h2 = 0x3c6ef372fe94f82b;
	unsigned long	h3 = 0xa54ff53a5f1d36f1;
	unsigned long	h4 = 0x510e527fade682d1;
	unsigned long	h5 = 0x9b05688c2b3e6c1f;
	unsigned long	h6 = 0x1f83d9abfb41bd6b;
	unsigned long	h7 = 0x5be0cd19137e2179;
	unsigned long	k[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd,
							 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
							 0x3956c25bf348b538, 0x59f111f1b605d019,
							 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
							 0xd807aa98a3030242, 0x12835b0145706fbe,
							 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
							 0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
							 0x9bdc06a725c71235, 0xc19bf174cf692694,
							 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
							 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
							 0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
							 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
							 0x983e5152ee66dfab, 0xa831c66d2db43210,
							 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
							 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
							 0x06ca6351e003826f, 0x142929670a0e6e70,
							 0x27b70a8546d22ffc, 0x2e1b21385c26c926,
							 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
							 0x650a73548baf63de, 0x766a0abb3c77b2a8,
							 0x81c2c92e47edaee6, 0x92722c851482353b,
							 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
							 0xc24b8b70d0f89791, 0xc76c51a30654be30,
							 0xd192e819d6ef5218, 0xd69906245565a910,
							 0xf40e35855771202a, 0x106aa07032bbd1b8,
							 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
							 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
							 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
							 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
							 0x748f82ee5defb2fc, 0x78a5636f43172f60,
							 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
							 0x90befffa23631e28, 0xa4506cebde82bde9,
							 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
							 0xca273eceea26619c, 0xd186b8c721c0c207,
							 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
							 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
							 0x113f9804bef90dae, 0x1b710b35131c471b,
							 0x28db77f523047d84, 0x32caab7b40c72493,
							 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
							 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
							 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

	// Set the 1024 block with padding
	memset(b1024, 0, 128);
	memcpy(b1024, str, strlen(str));
	b1024[strlen(str)] = 1 << 7;
	*(unsigned long*)(b1024 + 120) = strlen(str) * 8 % UINT_MAX;
	*(unsigned long*)(b1024 + 112) = strlen(str) * 8 / UINT_MAX;
	switch_endianess(b1024 + 112);
	switch_endianess(b1024 + 120);
	//*(unsigned int*)(b512 + 56) = strlen(str) * 8 % UINT_MAX;
	//*(unsigned int*)(b512 + 60) = strlen(str) * 8 / UINT_MAX;
	memset(result, 0, 128);

	// Print the 1024 block
	write(1, "START\n", 6);
	write(1, b1024, 64);
	write(1, "\n", 1);

	// Divise the 1024 block in 16 blocks of 64 bits
	for (unsigned int i = 0; i < 32; i++)
	{
		m[i] = 0;
		m[i] |= *(b1024 + i * 4 + 3) & 255;
		m[i] |= *(b1024 + i * 4 + 2) << 8 & 65280;
		m[i] |= *(b1024 + i * 4 + 1) << 16 & 16711680;
		m[i] |= *(b1024 + i * 4 ) << 24 & 4278190080;
		printf("m[%2u] %08x  ", i, m[i]);
		if (i && i % 4 == 3)
			printf("\n");
	}

	// Loop for each 1024 blocks but not here
	unsigned long	a = h0;
    unsigned long	b = h1;
    unsigned long	c = h2;
    unsigned long	d = h3;
    unsigned long	e = h4;
    unsigned long	f = h5;
    unsigned long	g = h6;
    unsigned long	h = h7;
    unsigned long	s0, s1;
	unsigned long	ch, ma, t1, t2;

	// Main loop
	for (unsigned int i = 16; i < 80; i++)
	{
		s0 = rotr64(m[i - 15], 1) ^ rotr64(m[i - 15], 8) ^ (m[i - 15] >> 7);
		s1 = rotr64(m[i - 2], 19) ^ rotr64(m[i - 2], 61) ^ (m[i - 2] >> 6);
		m[i] = m[i - 16] + s0 + m[i - 7] + s1;
	}
	for (unsigned int i = 0; i < 80; i++)
	{
		ch = (e & f) ^ ((~e) & g);
		ma = (a & b) ^ (a & c) ^ (b & c);
		s0 = rotr64(a, 28) ^ rotr64(a, 34) ^ rotr64(a, 39);
		s1 = rotr64(e, 14) ^ rotr64(e, 18) ^ rotr64(e, 41);
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
		printf("%2u. %016lx %016lx %016lx %016lx\n    %016lx %016lx %016lx %016lx\n",
			i, a, b, c, d, e, f, g, h);
		exit(0);
	}

	// Inside the loop of each 1024 block
	h0 += a;
	h1 += b;
	h2 += c;
	h3 += d;
	h4 += e;
	h5 += f;
	h6 += g;
	h7 += h;

	// Recompose the result
	printf("A %016x\n", h0);
	printf("B %016x\n", h1);
	printf("C %016x\n", h2);
	printf("D %016x\n", h3);
	printf("E %016x\n", h4);
	printf("F %016x\n", h5);
	printf("G %016x\n", h6);
	printf("H %016x\n", h7);
	memcpy(result, &h0, 8);
	memcpy(result + 8, &h1, 8);
	memcpy(result + 16, &h2, 8);
	memcpy(result + 24, &h3, 8);
	memcpy(result + 32, &h4, 8);
	memcpy(result + 40, &h5, 8);
	memcpy(result + 48, &h6, 8);
	memcpy(result + 56, &h7, 8);
	for (unsigned int i = 0; i < 64; i += 8)
		switch_endianess(result + i);

	// Print the result
	for (unsigned int i = 0; i < 128; i++)
	{
		printf("%02hhx", result[i]);
		if (i == 63 || i == 127)
			printf("\n");
	}

	// Print the final result from wikipedia
	write(1, "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a\n", 65);
	write(1, "2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f\n", 65);
	// write(1, "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592\n", 65);
	// write(1, "ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c\n", 65);
	return (0);
}


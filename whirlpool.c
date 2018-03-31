/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhezard <jhezard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 20:37:37 by jhezard           #+#    #+#             */
/*   Updated: 2018/03/31 21:02:09 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

void    switch_endianess(char *s)
{
	char    tmp[8];

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
	char			b512[64];
	unsigned int	result[64];
	unsigned int	m[64];

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
	memset(result, 0, 64);

	// Print the  512 block
	write(1, "START\n", 6);
	write(1, b512, 64);
	write(1, "\n", 1);

	// Divise the 512 block in 64 blocks iof 32 bits
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

		// Print to compare with
		write(1, "4E2448A4C6F486BB 16B6562C73B4020B F3043E3A731BCE72 1AE1B303D97E6D4C\n7181EEBDB6C57E27 7D0E34957114CBD6 C797FC9D95D8B582 D225292076D4EEF5\n", 136);
		return (0);
}

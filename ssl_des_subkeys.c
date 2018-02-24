/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des_subkeys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/24 12:48:22 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static int	ft_bit(int n)
{
	int r;

	r = BIT_8;
	while (n)
	{
		r /= 2;
		n--;
	}
	return (r);
}

void		des_shift_keys(t_des *des, int round, int encode)
{
	int		i;
	char	l;
	char	r;

	i = 0;
	l = des->leftkey[0] & BIT_7;
	r = des->rightkey[0] & BIT_7;
	while (i < 3)
	{
		des->leftkey[i] = (des->leftkey[i] & 63) << 1;
		des->rightkey[i] = (des->rightkey[i] & 63) << 1;
		des->leftkey[i] |= (des->leftkey[i + 1] & BIT_7) >> 6;
		des->rightkey[i] |= (des->rightkey[i + 1] & BIT_7) >> 6;
		i++;
	}
	des->leftkey[i] = ((des->leftkey[i] & 63) << 1) | (l >> 6);
	des->rightkey[i] = ((des->rightkey[i] & 63) << 1) | (r >> 6);
	if (round == 1 || round == 16 || (encode && (round == 2 || round == 9))
		|| (!encode && (round == 15 || round == 8)))
		return ;
	des_shift_keys(des, 1, encode);
}

void		des_permuted_choice_1(t_des *des)
{
	int		i;
	int		j;

	i = 248;
	j = 7;
	while (i != 192 && j--)
	{
		if (des->key[(i % 64) / 8] & (ft_bit((248 - i) / 64)))
			des->leftkey[0] |= 1 << j;
		if (des->key[((i - 55) % 64) / 8] & (ft_bit((304 - i) / 64)))
			des->leftkey[1] |= 1 << j;
		if (des->key[((i - 110) % 64) / 8] & (ft_bit((360 - i) / 64)))
			des->leftkey[2] |= 1 << j;
		if (des->key[((i - 165) % 64) / 8] & (ft_bit((416 - i) / 64)))
			des->leftkey[3] |= 1 << j;
		if (des->key[((i + 6) % 64) / 8] & (ft_bit(6 - (254 - i) / 64)))
			des->rightkey[0] |= 1 << j;
		if (des->key[((i - 51) % 64) / 8] & (ft_bit(6 - (305 - i) / 64)))
			des->rightkey[1] |= 1 << j;
		if (des->key[((i - 108) % 64) / 8] & (ft_bit(6 - (362 - i) / 64)))
			des->rightkey[2] |= 1 << j;
		if (i - 165 < 67 && des->key[((i - 197) % 64) / 8]
			& (ft_bit(6 - (254 - (i - 197)) / 64)))
			des->rightkey[3] |= 1 << j;
		else if (i - 165 >= 67 && des->key[((i - 165) % 64) / 8]
			& (ft_bit(6 - (254 - (i - 165)) / 64)))
			des->rightkey[3] |= 1 << j;
		i -= 8;
	}
}

void		des_create_key(t_env *e, t_des *des)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = getpass("enter des encryption password:");
	if (!(tmp2 = ft_strnew(ft_strlen(tmp1))))
		ssl_memory_error(e, des, __FUNCTION__);
	tmp2 = ft_strcpy(tmp2, tmp1);
	tmp1 = getpass("Verifying - enter des encryption password:");
	printf("%s | %s\n", tmp1, tmp2);
	if (ft_strcmp(tmp1, tmp2))
	{
		ft_putendl("Wrong password.");
		ssl_free_env(e);
		ft_memdel((void**)&tmp1);
		ft_memdel((void**)&tmp2);
		exit(0);
	}
	ft_memcpy(des->key, tmp1, 8);
	ft_memdel((void**)&tmp1);
	ft_memdel((void**)&tmp2);
}

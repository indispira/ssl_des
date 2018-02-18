/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/18 22:52:35 by jhezard          ###   ########.fr       */
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

void		des_final_permutation(t_des *des, int id)
{
	int		i;
	int		j;

	i = 39;
	j = 0;
	while (i < 64)
	{
		if (des->left[i / 8 - 4] & ft_bit(i % 8))
			des->ciphers[id][j / 4] |= 1 << (7 - (j * 2) % 8);
		i -= 32;
		if (des->right[i / 8] & ft_bit(i % 8))
			des->ciphers[id][j / 4] |= 1 << (7 - (j * 2 + 1) % 8);
		i += 40;
		if (i > 64)
			i -= 33;
		j++;
	}
}

void		des_feistel_network(t_des *des)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (i % 2 == 0)
		{
			des_function_f(des, i, des->right);
			des->left[0] = des->left[0] ^ des->perm[0];
			des->left[1] = des->left[1] ^ des->perm[1];
			des->left[2] = des->left[2] ^ des->perm[2];
			des->left[3] = des->left[3] ^ des->perm[3];
		}
		else
		{
			des_function_f(des, i, des->left);
			des->right[0] = des->right[0] ^ des->perm[0];
			des->right[1] = des->right[1] ^ des->perm[1];
			des->right[2] = des->right[2] ^ des->perm[2];
			des->right[3] = des->right[3] ^ des->perm[3];
		}
	}
}

void		des_initial_permutation(t_des *des, int id)
{
	int		i;

	ft_memset(des->left, 0, 4);
	ft_memset(des->right, 0, 4);
	i = 57;
	while (i != -1)
	{
		if (des->blocks[id][i / 8] & ft_bit(i % 8))
			des->left[(i % 8 - 1) / 2] |= 1 << i / 8;
		if (des->blocks[id][(i - 1) / 8] & ft_bit((i - 1) % 8))
			des->right[(i % 8 - 1) / 2] |= 1 << i / 8;
		if (i < 7)
			i += 66;
		i -= 8;
	}
}

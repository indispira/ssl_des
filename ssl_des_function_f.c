/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2017/02/18 17:13:43 by sboulet          ###   ########.fr       */
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

static void	des_expansion_e(t_des *des, char *block)
{
	int i;
	int j;

	// printf("Enter to %s\n", __FUNCTION__);
	i = 31;
	while (i != 63)
	{
		j = i - 1;
		while (++j < i + 6)
			if (block[(j % 32) / 8] & ft_bit(j % 8))
				des->exp[(i - 31) / 4] |= 1 << (5 - (j - i));
		i += 4;
	}
}

static void	des_reset_variables_function_f(t_des *des)
{
	// printf("Enter to %s\n", __FUNCTION__);
	ft_memset(des->exp, 0, 8);
	ft_memset(des->box, 0, 4);
	ft_memset(des->perm, 0, 4);
}

void		des_function_f(t_des *des, int id, char *block)
{
	int	i;

	// printf("Enter to %s                              Round %d\n", __FUNCTION__, id);
	des_reset_variables_function_f(des);
	des_expansion_e(des, block);
	i = -1;
	while (++i < 8)
		des->exp[i] = des->exp[i] ^ des->subkeys[id][i];
	constantes_des_s_boxes(des);
	constantes_des_permutation_p(des);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2017/02/18 17:13:43 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static void	des_cut_input_in_64bits_block(t_env *e, t_des *des)
{
	int i;

	printf("Enter to %s\n", __FUNCTION__);
	des_init_blocks(e, des);
	des_init_ciphers(e, des);
	i = -1;
	while (++i < e->length)
		// printf("%d / %d\n", i, e->length);
		des->blocks[i / 8][i % 8] = e->content[i];
}

int			des_encode(t_env *e)
{
	t_des	des;
	int		i;

	printf("Enter to %s\n", __FUNCTION__);
	des_init_struct(&des);
	if (e->flag & FLAG_K)
		ft_memcpy(des.key, e->pass, 8);
	else
		des_create_key(e, &des);
	des_permuted_choice_1(&des);
	i = 0;
	while (++i <= 16)
	{
		des_shift_keys(&des, i, 1);
		constantes_des_permuted_choice_2(&des, i - 1);
	}
	des_cut_input_in_64bits_block(e, &des);
	i = 0;
	while (des.blocks[i])
	{
		// printf("\nStart encoding the block : %s\n", des.blocks[i]);
		// printf("BLK: %3hhu %3hhu %3hhu %3hhu | %3hhu %3hhu %3hhu %3hhu\n",
		// 	des.blocks[i][0], des.blocks[i][1], des.blocks[i][2],
		// 	des.blocks[i][3], des.blocks[i][4], des.blocks[i][5],
		// 	des.blocks[i][6], des.blocks[i][7]);
		des_initial_permutation(&des, i);
		des_feistel_network(&des);
		des_final_permutation(&des, i);
		i++;
	}
	e->message = ft_memalloc(8 * e->nb_blocks + 1);
	e->length = e->nb_blocks * 8;
	i = 0;
	while (des.ciphers[i])
	{
		ft_memcpy(e->message + (i * 8), des.ciphers[i], 8);
		printf("CIP: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
			des.ciphers[i][0], des.ciphers[i][1], des.ciphers[i][2],
			des.ciphers[i][3], des.ciphers[i][4], des.ciphers[i][5],
			des.ciphers[i][6], des.ciphers[i][7]);
		i++;
	}
	return (0);
}

int			des_decode(t_env *e)
{
	t_des	des;
	int		i;

	printf("Enter to %s\n", __FUNCTION__);
	des_init_struct(&des);
	if (e->flag & FLAG_K)
		ft_memcpy(des.key, e->pass, 8);
	else
		des_create_key(e, &des);
	des_permuted_choice_1(&des);
	i = 17;
	while (--i > 0)
	{
		des_shift_keys(&des, i, 0);
		constantes_des_permuted_choice_2(&des, i - 1);
	}
	des_cut_input_in_64bits_block(e, &des);
	i = 0;
	while (des.blocks[i])
	{
		// printf("\nStart decoding the block : %s\n", des.blocks[i]);
		// printf("BLK: %3hhu %3hhu %3hhu %3hhu | %3hhu %3hhu %3hhu %3hhu\n",
		// 	des.blocks[i][0], des.blocks[i][1], des.blocks[i][2],
		// 	des.blocks[i][3], des.blocks[i][4], des.blocks[i][5],
		// 	des.blocks[i][6], des.blocks[i][7]);
		des_initial_permutation(&des, i);
		des_feistel_network(&des);
		des_final_permutation(&des, i);
		i++;
	}
	e->message = ft_memalloc(8 * e->nb_blocks + 1);
	e->length = e->nb_blocks * 8;
	i = 0;
	while (des.ciphers[i])
	{
		ft_memcpy(e->message + (i * 8), des.ciphers[i], 8);
		printf("CIP: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
			des.ciphers[i][0], des.ciphers[i][1], des.ciphers[i][2],
			des.ciphers[i][3], des.ciphers[i][4], des.ciphers[i][5],
			des.ciphers[i][6], des.ciphers[i][7]);
		i++;
	}
	return (0);
}
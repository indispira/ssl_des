/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/03/02 01:22:10 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static void	des_cut_input_in_64bits_block(t_env *e, t_des *des)
{
	int	i;

	des_init_blocks(e, des);
	des_init_ciphers(e, des);
	i = -1;
	while (++i < e->length && i < e->nb_blocks * 8)
		des->blocks[i / 8][i % 8] = e->data[i];
	if (!(e->flag & FLAG_D))
		while (i % 8 || (!(e->length % 8) && i < e->length + 8))
		{
			des->blocks[i / 8][i % 8] = e->length % 8 ? 8 - e->length % 8 : 8;
			i++;
		}
	else if (e->length % 8 != 0)
		ssl_error_length(e, des, 64);
	e->length = i;
}

static void	des_xor_block(t_env *e, t_des *des, int index)
{
	int	i;

	i = -1;
//	printf("IV : %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
//		des->iv[0], des->iv[1], des->iv[2], des->iv[3],
//		des->iv[4], des->iv[5], des->iv[6], des->iv[7]);
//	if (e->flag & FLAG_D)
//		printf("BLK: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
//		des->ciphers[index][0], des->ciphers[index][1],
//		des->ciphers[index][2], des->ciphers[index][3],
//		des->ciphers[index][4], des->ciphers[index][5],
//		des->ciphers[index][6], des->ciphers[index][7]);
//	else
//		printf("BLK: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
//		des->blocks[index][0], des->blocks[index][1],
//		des->blocks[index][2], des->blocks[index][3],
//		des->blocks[index][4], des->blocks[index][5],
//		des->blocks[index][6], des->blocks[index][7]);
	while (++i < 8)
	{
		if (e->flag & FLAG_D)
			des->ciphers[index][i] = des->ciphers[index][i] ^ des->iv[i];
		else
			des->blocks[index][i] = des->blocks[index][i] ^ des->iv[i];
	}
//	if (e->flag & FLAG_D)
//		printf("XOR: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
//		des->ciphers[index][0], des->ciphers[index][1],
//		des->ciphers[index][2], des->ciphers[index][3],
//		des->ciphers[index][4], des->ciphers[index][5],
//		des->ciphers[index][6], des->ciphers[index][7]);
//	else
//		printf("XOR: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
//		des->blocks[index][0], des->blocks[index][1],
//		des->blocks[index][2], des->blocks[index][3],
//		des->blocks[index][4], des->blocks[index][5],
//		des->blocks[index][6], des->blocks[index][7]);
}

static void	des_depadding(t_env *e, t_des *des)
{
	int		i;
	int		new_len;

	i = e->out[e->length - 1];
	if (i > 8 || i < 1)
		des_error_depadding(e, des);
	new_len = e->length - i;
	while (i--)
		e->out[new_len + i] = '\0';
	e->length = new_len;
}

void		des_encode(t_env *e, const char *pass, char flag)
{
	t_des	des;
	int		i;

//	dprintf(2, "Enter to %s\n", __FUNCTION__);
	des_init_struct(e, &des);
	if (flag)
		ft_memcpy(des.key, pass, 8);
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
		if (e->cmd & CBC || e->cmd & CBC3)
			des_xor_block(e, &des, i);
		des_initial_permutation(&des, i);
		des_feistel_network(&des);
		des_final_permutation(&des, i);
		if (e->cmd & CBC || e->cmd & CBC3)
			ft_memcpy(des.iv, des.ciphers[i], 8);
		i++;
	}
	e->out = ft_memalloc(8 * e->nb_blocks + 1);
	e->length = e->nb_blocks * 8;
	i = 0;
	while (des.ciphers[i])
	{
		ft_memcpy(e->out + (i * 8), des.ciphers[i], 8);
//		printf("CIP: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
//			des.ciphers[i][0], des.ciphers[i][1], des.ciphers[i][2],
//			des.ciphers[i][3], des.ciphers[i][4], des.ciphers[i][5],
//			des.ciphers[i][6], des.ciphers[i][7]);
		i++;
	}
	des_free_stc(&des);
}

void		des_decode(t_env *e, const char *pass, char flag)
{
	t_des	des;
	int		i;

//	dprintf(2, "Enter to %s\n", __FUNCTION__);
	des_init_struct(e, &des);
	if (flag)
		ft_memcpy(des.key, pass, 8);
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
//		printf("STA: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
//		des.blocks[i][0], des.blocks[i][1],
//		des.blocks[i][2], des.blocks[i][3],
//		des.blocks[i][4], des.blocks[i][5],
//		des.blocks[i][6], des.blocks[i][7]);
		if (e->cmd & CBC || e->cmd & CBC3)
			ft_memcpy(des.iv2, des.blocks[i], 8);
		des_initial_permutation(&des, i);
		des_feistel_network(&des);
		des_final_permutation(&des, i);
		if (e->cmd & CBC || e->cmd & CBC3)
		{
			des_xor_block(e, &des, i);
			ft_memcpy(des.iv, des.iv2, 8);
		}
		i++;
	}
	e->out = ft_memalloc(8 * e->nb_blocks + 1);
	e->length = e->nb_blocks * 8;
	i = 0;
	while (des.ciphers[i])
	{
		ft_memcpy(e->out + (i * 8), des.ciphers[i], 8);
//		printf("CIP: %2hhx %2hhx %2hhx %2hhx | %2hhx %2hhx %2hhx %2hhx\n",
//			des.ciphers[i][0], des.ciphers[i][1], des.ciphers[i][2],
//			des.ciphers[i][3], des.ciphers[i][4], des.ciphers[i][5],
//			des.ciphers[i][6], des.ciphers[i][7]);
		i++;
	}
	des_depadding(e, &des);
	des_free_stc(&des);
}

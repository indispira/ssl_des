/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2017/02/18 17:13:43 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

void	ssl_init_env(t_env *e)
{
	e->cmd = 0;
	e->flag = 0;
	e->pass = NULL;
	e->infile = NULL;
	e->outfile = NULL;
	e->data = NULL;
	e->out = NULL;
	e->nb_blocks = 0;
	e->length = 0;
}

void	des_init_ciphers(t_env *e, t_des *des)
{
	int i;
	int size;

	printf("Enter to %s\n", __FUNCTION__);
	size = e->length / 8 + 1;
	size = e->length % 8 ? size + 1 : size;
	if (!(des->ciphers = malloc(sizeof(char*) * size)))
	{
		ft_putendl("Memory allocation for Ciphers has failed.");
		ssl_free_env(e);
		exit(0);
	}
	i = -1;
	while (++i < size - 1)
	{
		if (!(des->ciphers[i] = ft_strnew(8)))
		{
			ft_putstr("Memory allocation for Cipher number ");
			ft_putnbr(i);
			ft_putendl(" has failed.");
			ssl_free_env(e);
			exit(0);
		}
	}
	des->ciphers[i] = NULL;
}

void	des_init_blocks(t_env *e, t_des *des)
{
	int i;
	int size;

	printf("Enter to %s\n", __FUNCTION__);
	size = e->length / 8 + 1;
	size = e->length % 8 ? size + 1 : size;
	e->nb_blocks = size - 1;
	if (!(des->blocks = malloc(sizeof(char*) * size)))
	{
		ft_putendl("Memory allocation for Blocks has failed.");
		ssl_free_env(e);
		exit(0);
	}
	i = -1;
	while (++i < size - 1)
	{
		if (!(des->blocks[i] = ft_strnew(8)))
		{
			ft_putstr("Memory allocation for Block number ");
			ft_putnbr(i);
			ft_putendl(" has failed.");
			ssl_free_env(e);
			exit(0);
		}
	}
	des->blocks[i] = NULL;
}

void	des_init_struct(t_des *des)
{
	int i;

	printf("Enter to %s\n", __FUNCTION__);
	ft_memset(des->key, 0, 8);
	ft_memset(des->leftkey, 0, 4);
	ft_memset(des->rightkey, 0, 4);
	i = -1;
	while (++i < 16)
		ft_memset(des->subkeys[i], 0, 8);
	des->blocks = NULL;
	des->ciphers = NULL;
	ft_memset(des->left, 0, 4);
	ft_memset(des->right, 0, 4);
	ft_memset(des->exp, 0, 8);
	ft_memset(des->box, 0, 4);
	ft_memset(des->perm, 0, 4);
}

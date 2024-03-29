/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/03/02 01:19:06 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

void		ssl_free_env(t_env *e)
{
	if (e->data)
		ft_memdel((void**)&e->data);
	if (e->out)
		ft_memdel((void**)&e->out);
}

void		des_free_stc(t_des *des)
{
	int		i;

	i = -1;
	if (des->blocks)
	{
		while (des->blocks[++i])
			ft_memdel((void**)&des->blocks[i]);
		ft_memdel((void**)&des->blocks);
	}
	i = -1;
	if (des->ciphers)
	{
		while (des->ciphers[++i])
			ft_memdel((void**)&des->ciphers[i]);
		ft_memdel((void**)&des->ciphers);
	}
}

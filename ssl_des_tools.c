/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/24 18:27:50 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

void	des_switch_data(t_env *e)
{
	ft_memdel((void**)&e->data);
	e->data = e->out;
	e->out = NULL;
}

void	des_str_to_hex(t_env *e, t_des *des)
{
	int	i;

	i = -1;
	while (++i < 8 && e->iv[i * 2] && e->iv[i * 2 + 1])
		des->iv[i] = ft_hex(e->iv[i * 2]) * 16 + ft_hex(e->iv[i * 2 + 1]);
}








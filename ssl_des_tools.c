/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/03/02 00:18:49 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

void	des_switch_data(t_env *e)
{
	ft_memdel((void**)&e->data);
	e->data = e->out;
	e->out = NULL;
}

void	des_str_to_hex(t_des *des, char *str)
{
	int	i;

	i = -1;
	while (++i < 8 && str[i * 2] && str[i * 2 + 1])
		des->iv[i] = ft_hex(str[i * 2]) * 16 + ft_hex(str[i * 2 + 1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/04 19:44:50 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static void	ssl_dispatch(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->cmd & B64)
		ssl_dispatch_base64(e);
	else if (e->cmd & DES)
		ssl_dispatch_des_ecb(e);
	else if (e->cmd & CBC)
		ssl_dispatch_des_cbc(e);
	else if (e->cmd & DES3)
		ssl_dispatch_des3_ecb(e);
	else if (e->cmd & CBC3)
		ssl_dispatch_des3_cbc(e);
}

int			main(int ac, char **av)
{
	t_env	e;

	if (ac == 1)
		write(1, "usage: ft_ssl command [command opts] [command args]\n", 52);
	else
	{
		ssl_init_env(&e);
		if (ssl_parse(ac, av, &e) && ssl_read(&e))
		{
			ssl_dispatch(&e);
			ssl_output(&e);
		}
		ssl_free_env(&e);
	}
	return (0);
}

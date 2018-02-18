/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/18 16:42:51 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

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

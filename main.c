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

static void	ssl_dispatch_flag_a(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (!(e->flag & FLAG_D))
	{
		ft_memdel((void**)&e->content);
		e->content = e->message;
		e->message = NULL;
		base64_encode(e, e->content, e->message);
	}
	else
	{
		base64_decode(e, e->content, e->message);
		ft_memdel((void**)&e->content);
		e->content = e->message;
		e->message = NULL;
		des_decode(e);
	}
}

static void	ssl_dispatch(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->flag & FLAG_A && !(e->cmd & B64) && e->flag & FLAG_D)
		ssl_dispatch_flag_a(e);
	else if (e->cmd & B64 && e->flag & FLAG_D)
		base64_decode(e, e->content, e->message);
	else if (e->cmd & B64)
		base64_encode(e, e->content, e->message);
	else if (e->cmd & DES)
	{
		if (e->flag & FLAG_D)
			des_decode(e);
		else
			des_encode(e);
		if (e->flag & FLAG_A && !(e->flag & FLAG_D))
			ssl_dispatch_flag_a(e);
	}
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

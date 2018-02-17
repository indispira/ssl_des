/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/17 16:32:21 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static void	ssl_flag_a(t_env *e)
{
	if (e->flag & FLAG_D)
	{
		base64_clean(e);
		base64_decode(e, e->data, e->out);
		ft_memdel((void**)&e->data);
		e->data = e->out;
		e->out = NULL;
	}
	else
	{
		ft_memdel((void**)&e->data);
		e->data = e->out;
		e->out = NULL;
		base64_encode(e, e->data, e->out);
	}

}

void	ssl_dispatch_base64(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->flag & FLAG_D)
	{
		base64_clean(e);
		base64_decode(e, e->data, e->out);
	}
	else
		base64_encode(e, e->data, e->out);
}

void	ssl_dispatch_des(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->flag & FLAG_D)
	{
		ssl_flag_a(e);
		des_decode(e, e->pass1);
	}
	else
	{
		des_encode(e, e->pass1);
		ssl_flag_a(e);
	}
}

void	ssl_dispatch_des3(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->flag & FLAG_D)
	{
		ssl_flag_a(e);
		des_decode(e, e->pass1);
		des_encode(e, e->pass2);
		des_decode(e, e->pass3);
	}
	else
	{
		des_encode(e, e->pass1);
		des_decode(e, e->pass2);
		des_encode(e, e->pass3);
		ssl_flag_a(e);
	}
}

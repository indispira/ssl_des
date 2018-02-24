/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/24 13:59:46 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static void	ssl_flag_a(t_env *e)
{
	if (e->flag & FLAG_D)
	{
		base64_clean(e);
		base64_decode(e, e->data, e->out);
		des_switch_data(e);
	}
	else
	{
		des_switch_data(e);
		base64_encode(e, e->data, e->out);
	}

}

static void	ssl_dispatch_base64(t_env *e)
{
	if (e->flag & FLAG_D)
	{
		base64_clean(e);
		base64_decode(e, e->data, e->out);
	}
	else
		base64_encode(e, e->data, e->out);
}

static void	ssl_dispatch_des(t_env *e)
{
	if (e->flag & FLAG_D)
	{
		ssl_flag_a(e);
		des_decode(e, e->pass1, e->flag & FLAG_K1);
	}
	else
	{
		des_encode(e, e->pass1, e->flag & FLAG_K1);
		ssl_flag_a(e);
	}
}

static void	ssl_dispatch_des3(t_env *e)
{
	if (e->flag & FLAG_D)
	{
		ssl_flag_a(e);
		des_decode(e, e->pass1, e->flag & FLAG_K1);
		e->flag = e->flag ^ FLAG_D;
		des_switch_data(e);
		des_encode(e, e->pass2, e->flag & FLAG_K2);
		e->flag = e->flag ^ FLAG_D;
		des_switch_data(e);
		des_decode(e, e->pass3, e->flag & FLAG_K3);
	}
	else
	{
		des_encode(e, e->pass1, e->flag & FLAG_K1);
		e->flag = e->flag ^ FLAG_D;
		des_switch_data(e);
		des_decode(e, e->pass2, e->flag & FLAG_K2);
		e->flag = e->flag ^ FLAG_D;
		des_switch_data(e);
		des_encode(e, e->pass3, e->flag & FLAG_K3);
		ssl_flag_a(e);
	}
}

void		ssl_dispatch(t_env *e)
{
	if (e->cmd & B64)
		ssl_dispatch_base64(e);
	else if (e->cmd & DES || e->cmd & CBC)
		ssl_dispatch_des(e);
	else if (e->cmd & DES3 || e->cmd & CBC3)
		ssl_dispatch_des3(e);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/04 19:44:50 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

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

void	ssl_dispatch_des_ecb(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->flag & FLAG_D)
	{
		if (e->flag & FLAG_A)
		{
			base64_clean(e);
			base64_decode(e, e->data, e->out);
			ft_memdel((void**)&e->data);
			e->data = e->out;
			e->out = NULL;
		}
		des_decode(e);
	}
	else
	{
		des_encode(e);
		if (e->flag & FLAG_A)
		{
			ft_memdel((void**)&e->data);
			e->data = e->out;
			e->out = NULL;
			base64_encode(e, e->data, e->out);
		}
	}
}

void	ssl_dispatch_des_cbc(t_env *e)
{
	(void)e;
}

void	ssl_dispatch_des3_ecb(t_env *e)
{
	(void)e;
}

void	ssl_dispatch_des3_cbc(t_env *e)
{
	(void)e;
}

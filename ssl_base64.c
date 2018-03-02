/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_base64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/03/02 01:21:36 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static char	base64_table(char n, char encode)
{
	if (encode)
	{
		if (n < 26)
			return ('A' + n);
		else if (n < 52)
			return ('a' + n - 26);
		else if (n < 62)
			return ('0' + n - 52);
		return (n == 62 ? '+' : '/');
	}
	if (n >= 'A' && n <= 'Z')
		return (n - 'A');
	else if (n >= 'a' && n <= 'z')
		return (n - 'a' + 26);
	else if (n >= '0' && n <= '9')
		return (n - '0' + 52);
	return (n == '+' ? 62 : 63);
}

static char	*base64_encode2(int i, char c, char *s, char *msg)
{
	if (i % 4 == 2)
	{
		c = *s & 15;
		s++;
		if (!(*s) && (*msg = base64_table(c << 2, 1)))
			ft_strcat(++msg, "=");
		else
			*msg = base64_table((c << 2) + ((*s & 192) >> 6), 1);
	}
	else if (i % 4 == 3)
	{
		c = *s & 3;
		s++;
		if (!(*s) && (*msg = base64_table(c << 4, 1)))
			ft_strcat(++msg, "==");
		else
			*msg = base64_table((c << 4) + ((*s & 240) >> 4), 1);
	}
	return (s);
}

void		base64_encode(t_env *e, char *s, char *msg)
{
	int		i;
	int		size;

	i = 0;
	size = e->length * 4 / 3 + 4;
	if (!(e->out = ft_strnew(size)))
		ssl_memory_error(e, NULL, __FUNCTION__);
	msg = e->out;
	while (s < e->data + e->length)
	{
		if (i % 4 == 0)
			*msg = base64_table((*s & 252) >> 2, 1);
		else if (i % 4 == 1)
		{
			*msg = base64_table(*s & 63, 1);
			s++;
		}
		else
			s = base64_encode2(i, 0, s, msg);
		i += 3;
		msg++;
	}
	e->length = ft_strlen(e->out);
}

void		base64_decode(t_env *e, char *s, char *msg)
{
	int		i;
	char	c;

	i = 0;
	if (!(e->out = ft_strnew(e->length)))
		ssl_memory_error(e, NULL, __FUNCTION__);
	msg = e->out;
	while (*s && *s != '=')
	{
		if (i % 4 == 0)
			c = base64_table(*s, 0) << 2;
		else if (i % 4 == 1)
			*(msg++) = c + base64_table(*s, 0);
		else if (i % 4 == 2)
		{
			*(msg++) = c + ((base64_table(*s, 0) & 60) >> 2);
			c = (base64_table(*s, 0) & 3) << 6;
		}
		else if (i % 4 == 3)
		{
			*(msg++) = c + ((base64_table(*s, 0) & 48) >> 4);
			c = (base64_table(*s, 0) & 15) << 4;
		}
		i += (s++) ? 3 : 0;
	}
	e->length = msg - e->out;
}

void		base64_clean(t_env *e)
{
	char	*clean;
	char	*src;
	char	*dest;

	if (!(clean = malloc(sizeof(char) * (e->length + 1))))
	{
		ft_putendl("Memory allocation for clean data in base64 has failed.");
		ssl_free_env(e);
		exit(0);
	}
	ft_bzero(clean, e->length + 1);
	src = e->data;
	dest = clean;
	while (*src)
	{
		if (*src != '\n')
		{
			*dest = *src;
			dest++;
		}
		src++;
	}
	ft_memdel((void**)&e->data);
	e->data = clean;
	e->length = ft_strlen(clean);
}

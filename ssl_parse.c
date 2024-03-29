/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/24 18:22:40 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static int	ssl_get_filename(t_env *e, int ac, char **av, int id)
{
	if (id + 1 >= ac)
		ssl_print_usage(e);
	if (!ft_strcmp("-i", av[id]) || !ft_strcmp("-in", av[id]))
	{
		e->flag |= FLAG_I;
		e->infile = av[id + 1];
	}
	if (!ft_strcmp("-o", av[id]) || !ft_strcmp("-out", av[id]))
	{
		e->flag |= FLAG_O;
		e->outfile = av[id + 1];
	}
	return (id + 1);
}

static int	ssl_get_passphrase(t_env *e, int ac, char **av, int id)
{
	if (id + 1 >= ac)
		ssl_print_usage(e);
	if (!ft_strcmp("-k", av[id]) || !ft_strcmp("-k1", av[id]))
	{
		e->flag |= FLAG_K1;
		e->pass1 = av[id + 1];
	}
	else if (!ft_strcmp("-k2", av[id]))
	{
		e->flag |= FLAG_K2;
		e->pass2 = av[id + 1];
	}
	else if (!ft_strcmp("-k3", av[id]))
	{
		e->flag |= FLAG_K3;
		e->pass3 = av[id + 1];
	}
	else if (!ft_strcmp("-v", av[id]))
	{
		e->flag |= FLAG_V;
		e->iv = av[id + 1];
	}
	return (id + 1);
}

static void	ssl_check_flags(t_env *e, char c)
{
	e->flag |= c == 'e' ? FLAG_E : 0;
	e->flag |= c == 'd' ? FLAG_D : 0;
	e->flag |= c == 'a' ? FLAG_A : 0;
	if (c != 'e' && c != 'd' && c != 'a')
		ssl_error_flags(&c, 1, e);
}

static int	ssl_args_parser(int ac, char **av, t_env *e)
{
	int			i;
	const char	*arg;

	i = 1;
	while (++i < ac)
	{
		arg = av[i];
		if (!ft_strcmp("-i", arg) || !ft_strcmp("-in", arg)
			|| !ft_strcmp("-o", arg) || !ft_strcmp("-out", arg))
			i = ssl_get_filename(e, ac, av, i);
		else if (!ft_strcmp("-k", arg) || !ft_strcmp("-k1", arg)
			|| !ft_strcmp("-k2", arg) || !ft_strcmp("-k3", arg)
			|| !ft_strcmp("-v", arg))
			i = ssl_get_passphrase(e, ac, av, i);
		else if (*arg == '-')
			while (*(++arg))
				ssl_check_flags(e, *arg);
		else
			ssl_error_flags(arg, 0, e);
	}
	return (e->flag & FLAG_E && e->flag & FLAG_D ? ssl_ed() : 1);
}

int			ssl_parse(int ac, char **av, t_env *e)
{
	if (!ft_strcmp("base64", av[1]))
		e->cmd = B64;
	else if (!ft_strcmp("des", av[1]) || !ft_strcmp("des-ecb", av[1]))
		e->cmd = DES;
	else if (!ft_strcmp("des-cbc", av[1]))
		e->cmd = CBC;
	else if (!ft_strcmp("des3", av[1]) || !ft_strcmp("des3-ecb", av[1]))
		e->cmd = DES3;
	else if (!ft_strcmp("des3-cbc", av[1]))
		e->cmd = CBC3;
	if (e->cmd)
		return (ssl_args_parser(ac, av, e));
	return (ssl_help(av[1]));
}

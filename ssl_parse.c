/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2017/02/18 17:13:43 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static int	ssl_help(char *s)
{
	write(2, "ft_ssl: Error: '", 16);
	write(2, s, ft_strlen(s));
	write(2, "' is an invalid command.\n\nStandard commands:\n\n", 46);
	write(2, "Message Digest commands:\n\nCipher commands:\n", 43);
	write(2, "base64\ndes\ndes-ecb\ndes-cbc\n", 27);
	return (0);
}

static int	ssl_get_next_arg(t_env *e, int ac, char **av, int id)
{
	if (id + 1 >= ac)
		e->cmd & B64 ? ssl_print_usage_base64() : ssl_print_usage_des();
	if (!ft_strcmp("-k", av[id]))
	{
		e->flag |= FLAG_K;
		e->pass = av[id + 1];
	}
	if (!ft_strcmp("-i", av[id]) || !ft_strcmp("-in", av[id]))
	{
		e->flag |= FLAG_I;
		e->input = av[id + 1];
	}
	if (!ft_strcmp("-o", av[id]) || !ft_strcmp("-out", av[id]))
	{
		e->flag |= FLAG_O;
		e->output = av[id + 1];
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

	printf("Enter to %s\n", __FUNCTION__);
	i = 1;
	while (++i < ac)
	{
		arg = av[i];
		if (!ft_strcmp("-k", arg) || !ft_strcmp("-i", arg)
			|| !ft_strcmp("-in", arg) || !ft_strcmp("-o", arg)
			|| !ft_strcmp("-out", arg))
			i = ssl_get_next_arg(e, ac, av, i);
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
	printf("Enter to %s\n", __FUNCTION__);
	if (!ft_strcmp("base64", av[1]))
		e->cmd = B64;
	if (!ft_strcmp("des", av[1]) || !ft_strcmp("des-ecb", av[1]))
		e->cmd = DES;
	if (!ft_strcmp("des-cbc", av[1]))
		e->cmd = CBC;
	if (e->cmd)
		return (ssl_args_parser(ac, av, e));
	return (ssl_help(av[1]));
}

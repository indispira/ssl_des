/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/03/01 23:42:37 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

void	ssl_memory_error(t_env *e, t_des *des, const char *fct)
{
	ft_putstr("Memory allocation in function ");
	ft_putstr(fct);
	ft_putendl(" has failed.");
	if (e)
		ssl_free_env(e);
	if (des)
		ft_putendl("Need implementation here"); //TODO
		// des_free_keys(des);
	exit(0);
}

int		ssl_ed(void)
{
	write(2, "Invalid combinaison of flags: ", 30);
	write(2, "impossible to encode and decode in the same time.\n", 50);
	return (0);
}

void	ssl_error_flags(const char *arg, char flag, t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->cmd & B64)
		ft_putstr_fd("base64:\tinvalid option -- ", 2);
	else if (e->cmd & DES)
		ft_putstr_fd("des:\tinvalid option -- ", 2);
	else if (e->cmd & CBC)
		ft_putstr_fd("des-cbc:\tinvalid option -- ", 2);
	else if (e->cmd & DES3)
		ft_putstr_fd("des3:\tinvalid option -- ", 2);
	else if (e->cmd & CBC3)
		ft_putstr_fd("des3-cbc:\tinvalid option -- ", 2);
	flag ? write(1, arg, 1) : ft_putstr(arg);
	if (e->cmd & B64 || e->cmd & DES || e->cmd & CBC3
		|| e->cmd & DES3 || e->cmd & CBC3)
		ssl_print_usage(e);
	exit(0);
}

int		ssl_help(char *s)
{
	write(2, "ft_ssl: Error: '", 16);
	write(2, s, ft_strlen(s));
	write(2, "' is an invalid command.\n\nStandard commands:\n\n", 46);
	write(2, "Message Digest commands:\n\nCipher commands:\n", 43);
	write(2, "base64\ndes\ndes-ecb\ndes-cbc\ndes3\ndes3-ecb\ndes3-cbc\n", 50);
	return (0);
}

void	ssl_error_length(t_env *e, t_des *des, int length)
{
	ssl_free_env(e);
	des_free_stc(des);
	write(2, "Wrong length of input data, need a length modulo ", 49);
	ft_putnbr_fd(length, 2);
	write(2, "bits.\n", 6);
	exit(0);
}

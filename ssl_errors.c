/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/04 16:55:57 by jhezard          ###   ########.fr       */
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

void	ssl_print_usage_base64(void)
{
	ft_putendl("\nUsage:\tbase64 [-ed] [-i input_file] [-o output_file]");
	ft_putstr("  -e\t\t\tencodes input\n  -d\t\t\tdecodes input\n");
	ft_putstr("  -i\t\t\tinput file\n  -o\t\t\toutput file\n");
}

void	ssl_print_usage_des(void)
{
	ft_putstr("\nUsage:\tdes [-eda] [-k passphrase] [-in input_file]");
	ft_putendl(" [-out output_file]");
	ft_putstr("  -e\t\t\tencodes input\n  -d\t\t\tdecodes input\n");
	ft_putstr("  -a\t\t\tbase64 encode/decode\n");
	ft_putstr("  -k\t\t\tpassphrase is the next argument\n");
	ft_putstr("  -in\t\t\tinput file\n  -out\t\t\toutput file\n");
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
	flag ? write(1, arg, 1) : ft_putstr(arg);
	if (e->cmd & B64)
		ssl_print_usage_base64();
	else if (e->cmd & DES || e->cmd & CBC)
		ssl_print_usage_des();
	exit(0);
}

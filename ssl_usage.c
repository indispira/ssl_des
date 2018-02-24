/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/24 14:06:22 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

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

void	ssl_print_usage_des3(void)
{
	ft_putstr("\nUsage:\tdes3 [-eda] [-k1 passphrase] [-k2 passphrase]");
	ft_putendl("[-k3 passphrase] [-in input_file] [-out output_file]");
	ft_putstr("  -e\t\t\tencodes input\n  -d\t\t\tdecodes input\n");
	ft_putstr("  -a\t\t\tbase64 encode/decode\n");
	ft_putstr("  -k1\t\t\tfirst passphrase is the next argument\n");
	ft_putstr("  -k2\t\t\tsecond passphrase is the next argument\n");
	ft_putstr("  -k3\t\t\tthird passphrase is the next argument\n");
	ft_putstr("  -in\t\t\tinput file\n  -out\t\t\toutput file\n");
}

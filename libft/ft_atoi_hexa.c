/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 16:22:34 by sboulet           #+#    #+#             */
/*   Updated: 2016/01/11 14:59:22 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_hexa(const char *str)
{
	int	i;
	int	n;
	int	d;

	i = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	d = i;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')
		|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		n = str[i] >= '0' && str[i] <= '9' ? n * 16 + str[i++] - '0' : n;
		n = str[i] >= 'a' && str[i] <= 'f' ? n * 16 + str[i++] - 'a' + 10 : n;
		n = str[i] >= 'A' && str[i] <= 'F' ? n * 16 + str[i++] - 'A' + 10 : n;
	}
	if (str[d] == '-')
		n = -n;
	return (n);
}

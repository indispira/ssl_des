/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 16:22:34 by sboulet           #+#    #+#             */
/*   Updated: 2016/01/09 16:32:09 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *str, int base)
{
	int	i;
	int	n;
	int	d;

	i = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	d = i;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')
		|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		n = str[i] >= '0' && str[i] <= '9' ? n * base + str[i++] - '0' : n;
		n = str[i] >= 'a' && str[i] <= 'f' ? n * base + str[i++] - 'a' + 10 : n;
		n = str[i] >= 'A' && str[i] <= 'F' ? n * base + str[i++] - 'A' + 10 : n;
	}
	if (str[d] == '-')
		n = -n;
	return (n);
}

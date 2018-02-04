/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:37:23 by sboulet           #+#    #+#             */
/*   Updated: 2016/03/03 17:57:01 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long	tmp;
	int		size;
	char	*str;

	tmp = n < 0 ? -(long)n : n;
	size = n < 0 ? 1 : 0;
	while (++size && tmp / 10)
		tmp /= 10;
	if ((str = ft_strnew(size)))
	{
		str[0] = n < 0 ? '-' : '\0';
		tmp = n < 0 ? -(long)n : n;
		str[size - 1] = n == 0 ? '0' : str[size - 1];
		while ((--size || 1) && tmp)
		{
			str[size] = tmp % 10 + '0';
			tmp /= 10;
		}
	}
	return (str);
}

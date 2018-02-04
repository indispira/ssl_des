/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 15:42:07 by sboulet           #+#    #+#             */
/*   Updated: 2016/01/09 15:45:13 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long n, int base, int cap)
{
	int			size;
	long long	tmp;
	char		*str;
	static char	b_min[36] = {"0123456789abcdefghijklmnopqrstuvwxyz"};
	static char	b_maj[36] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

	size = n <= 0 ? 1 : 0;
	tmp = n;
	while (tmp / base != 0)
		tmp = (size++ >= 0) ? tmp / base : tmp / base;
	str = ft_strnew(size);
	if (n == 0 && (str[0] = '0'))
		return (str);
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[size--] = cap == 0 ? b_min[ABS(n % base)] : b_maj[ABS(n % base)];
		n /= base;
	}
	return (str);
}

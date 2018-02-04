/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:22:40 by sboulet           #+#    #+#             */
/*   Updated: 2016/01/04 13:35:35 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	d;

	i = 0;
	while (dest[i] != '\0')
		i++;
	d = -1;
	while (++d < n)
		dest[i + d] = src[d];
	dest[i + d] = '\0';
	return (dest);
}

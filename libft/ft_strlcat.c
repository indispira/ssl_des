/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:22:40 by sboulet           #+#    #+#             */
/*   Updated: 2015/11/26 17:03:44 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s_d;
	size_t	s_s;

	s_d = ft_strlen(dst);
	s_s = ft_strlen(src);
	if (s_d + 1 > size)
		return (size + s_s);
	i = 0;
	while (i + s_d + 1 < size && src)
	{
		dst[i + s_d] = src[i];
		i++;
	}
	while (s_d + i < size)
	{
		dst[i + s_d] = '\0';
		i++;
	}
	return (s_d + s_s);
}

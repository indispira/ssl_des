/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 18:05:52 by sboulet           #+#    #+#             */
/*   Updated: 2015/11/26 12:26:03 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	int		end;

	i = -1;
	end = 0;
	while (++i < n)
	{
		if (src[i] != '\0' && end == 0)
			dst[i] = src[i];
		else
		{
			end = 1;
			dst[i] = '\0';
		}
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:57:37 by sboulet           #+#    #+#             */
/*   Updated: 2016/03/03 16:34:40 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*buffer;
	size_t	i;

	buffer = (void*)malloc(n);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char*)buffer)[i] = ((char*)src)[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		((char*)dest)[i] = ((char*)buffer)[i];
		i++;
	}
	free(buffer);
	return (dest);
}

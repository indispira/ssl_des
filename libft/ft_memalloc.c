/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:33:03 by sboulet           #+#    #+#             */
/*   Updated: 2015/11/25 14:40:02 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	mem = (void*)malloc(size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((char*)mem)[i] = 0;
		i++;
	}
	return (mem);
}

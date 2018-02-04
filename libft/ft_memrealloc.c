/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:40:17 by sboulet           #+#    #+#             */
/*   Updated: 2016/04/26 13:27:59 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrealloc(void *s, size_t old_size, size_t new_size)
{
	unsigned char	*tmp;

	if (!new_size || old_size == new_size)
		return (s);
	if ((tmp = (unsigned char*)ft_memalloc(sizeof(unsigned char) * new_size)))
	{
		old_size = (old_size < new_size) ? old_size : new_size;
		ft_memcpy(tmp, s, old_size);
		s = tmp;
	}
	return (s);
}

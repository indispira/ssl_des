/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:30:14 by sboulet           #+#    #+#             */
/*   Updated: 2015/11/26 14:01:20 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int buffer;

	i = -1;
	buffer = -1;
	while (s[++i] != '\0')
		if (s[i] == c)
			buffer = i;
	if (s[i] == c)
		buffer = i;
	if (buffer > -1)
		return (&((char*)s)[buffer]);
	return (NULL);
}

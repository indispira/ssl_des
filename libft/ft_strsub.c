/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:41:17 by sboulet           #+#    #+#             */
/*   Updated: 2015/12/13 18:19:12 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	str = (char*)malloc(sizeof(*str) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		str[i] = s[i + start];
		i++;
		len--;
	}
	str[i] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:07:27 by sboulet           #+#    #+#             */
/*   Updated: 2015/12/04 13:26:24 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
	str = (char*)malloc(sizeof(*str) * size + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

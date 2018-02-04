/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:00:05 by sboulet           #+#    #+#             */
/*   Updated: 2015/12/13 18:18:22 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;

	str = (char*)malloc(sizeof(*str) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		str[i] = f(s[i]);
	str[i] = '\0';
	return (str);
}

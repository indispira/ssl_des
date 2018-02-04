/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:59:17 by sboulet           #+#    #+#             */
/*   Updated: 2015/12/13 18:47:03 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		d;

	str = (char*)malloc(sizeof(*str) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	d = 0;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
	{
		i++;
		d++;
	}
	while (s[i] != '\0')
	{
		str[i - d] = s[i];
		i++;
	}
	i--;
	while (str[i - d] == ' ' || str[i - d] == '\n' || str[i - d] == '\t')
		str[(i--) - d] = '\0';
	return (str);
}

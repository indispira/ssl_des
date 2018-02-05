/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:26:30 by sboulet           #+#    #+#             */
/*   Updated: 2016/03/21 18:12:14 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_length(const char *str, char c)
{
	int	length;

	length = 0;
	while (*str != c && *str != '\0')
	{
		length++;
		str++;
	}
	return (length);
}

static int	ft_count_words(const char *str, char c)
{
	int	nb_w;
	int	word;

	nb_w = 0;
	word = 0;
	while (*str != '\0')
	{
		if (word == 1 && *str == c)
			word = 0;
		if (word == 0 && *str != c)
		{
			word = 1;
			nb_w++;
		}
		str++;
	}
	return (nb_w);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nb_words;
	int		i_tab;

	nb_words = ft_count_words(s, c);
	tab = (char**)malloc(sizeof(*tab) * (nb_words + 1));
	if (!tab)
		return (NULL);
	i_tab = 0;
	while (nb_words--)
	{
		while (*s == c && *s != '\0')
			s++;
		tab[i_tab] = ft_strsub(s, 0, ft_word_length(s, c));
		if (!tab[i_tab])
			return (NULL);
		s = s + ft_word_length(s, c);
		i_tab++;
	}
	tab[i_tab] = NULL;
	return (tab);
}

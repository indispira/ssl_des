/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:40:17 by sboulet           #+#    #+#             */
/*   Updated: 2016/02/12 13:32:01 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_stock(char *tab, char **line, int reading)
{
	char	end;
	int		tab_s;
	int		line_s;

	tab_s = 0;
	while (tab_s < BUFF_SIZE && tab[tab_s] != '\n' && tab[tab_s])
		tab_s++;
	line_s = *line ? ft_strlen(*line) : 0;
	*line = ft_memrealloc(*line, line_s, line_s + tab_s + 1);
	ft_memcpy(*line + line_s, tab, tab_s);
	if (tab_s != BUFF_SIZE)
	{
		end = tab[tab_s];
		ft_memmove(tab, tab + tab_s + 1, BUFF_SIZE - tab_s - 1);
		ft_memset(tab + BUFF_SIZE - tab_s - 1, 0, tab_s + 1);
		if (reading || *tab || end == '\n')
			return (1);
		return (0);
	}
	ft_memset(tab, 0, tab_s);
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	int			ret;
	char		*buf;
	static char	tab[MAX_FD][BUFF_SIZE];

	buf = NULL;
	if (fd < 0 || fd >= MAX_FD || !line)
		return (-1);
	if (tab[fd][0])
	{
		if ((ret = ft_stock(tab[fd], &buf, 0)))
			return ((*line = buf) ? ret : ret);
	}
	while ((ret = read(fd, tab[fd], BUFF_SIZE)) > 0)
	{
		if ((ret = ft_stock(tab[fd], &buf, 1)))
			return ((*line = buf) ? ret : ret);
	}
	if ((*line = buf) && ret != -1 && *buf)
		return (1);
	return (ret);
}

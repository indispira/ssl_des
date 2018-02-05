/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2017/02/18 17:13:43 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static int	read_stream(t_env *e, int fd)
{
	int		size;
	char	buffer[1024];
	char	*tmp;

	printf("Enter to %s\n", __FUNCTION__);
	tmp = NULL;
	while ((size = read(fd, buffer, 1024)) > 0)
	{
		if (!e->data)
			e->data = ft_memcpy(ft_strnew(size + 8), buffer, size);
		else
		{
			tmp = ft_memalloc(e->length + size + 2);
			ft_memcpy(tmp, e->data, e->length);
			ft_memdel((void**)&e->data);
			e->data = tmp;
			ft_memcpy(e->data + e->length, buffer, size);
		}
		e->length += size;
	}
	return (1);
}

static int	read_file(t_env *e)
{
	int		fd;

	printf("Enter to %s\n", __FUNCTION__);
	if ((fd = open(e->infile, O_RDONLY)) == -1)
	{
		ft_putendl_fd("Open of the input file has failed\n", 2);
		ssl_free_env(e);
		exit(0);
	}
	if (!(read_stream(e, fd)))
		return (0);
	if (close(fd) == -1)
	{
		ft_putendl_fd("Close of the input file has failed\n", 2);
		ssl_free_env(e);
		exit(0);
	}
	return (1);
}

int			ssl_read(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->flag & FLAG_I && !e->infile)
		return (write(2, "Requires an input file.\n", 24));
	if (e->flag & FLAG_I)
		return (read_file(e));
	else
		return (read_stream(e, 0));
}

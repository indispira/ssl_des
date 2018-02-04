/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2017/02/18 17:13:43 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static void	ssl_output_base64(t_env *e, int fd)
{
	int i;

	printf("Enter to %s\n", __FUNCTION__);
	i = 0;
	while (i < e->length)
	{
		write(fd, e->message + i, e->length - i > 63 ? 64 : e->length - i);
		write(fd, "\n", 1);
		i += 64;
	}
}

static void	ssl_output_file(t_env *e)
{
	int		fd;

	printf("Enter to %s\n", __FUNCTION__);
	if ((fd = open(e->output, O_RDWR | O_CREAT, 0644)) == -1)
	{
		ft_putendl("Open of the input file has failed\n");
		ssl_free_env(e);
		exit(0);
	}
	if (e->flag & FLAG_E && !(e->flag & FLAG_O))
		ft_putendl_fd(e->message, fd);
	else
	{
		if ((e->cmd & B64 && e->flag & FLAG_E)
			|| (e->cmd & DES && e->flag & FLAG_A))
			ssl_output_base64(e, fd);
		// while (e->length > 0)
		// {
		// 	write(fd, e->message, e->length > 63 ? 64 : e->length);
		// 	write(fd, "\n", 1);
		// 	e->length -= 64;
		// }
		// printf("MESSAGE\n%s\n", e->message);
		else if (e->cmd & DES || (e->cmd & B64 && e->flag & FLAG_D))
		{
			write(fd, e->message, e->length - 8);
			ft_putstr_fd(e->message + e->length - 8, fd);
		}
		else
			ft_putstr_fd(e->message, fd);
		// write(fd, e->message, e->nb_blocks * 8);
		// exit(0);
	}
	if (close(fd) == -1)
	{
		ft_putendl("Close of the input file has failed\n");
		ssl_free_env(e);
		exit(0);
	}
}

void		ssl_output(t_env *e)
{
	printf("Enter to %s\n", __FUNCTION__);
	if (e->flag & FLAG_O && !e->output)
		write(2, "Requires an output file.\n", 24);
	else if (e->flag & FLAG_O)
		ssl_output_file(e);
	else if (e->flag & FLAG_E && e->cmd & B64)
		ft_putendl(e->message);
	else if (e->flag & FLAG_E)
	{
		write(1, e->message, e->length);
		// write(1, e->message, e->nb_blocks * 8);
		write(1, "\n", 1);
	}
	else
	{
		if (e->cmd & B64)
			ft_putstr(e->message);
		else
			write(1, e->message, e->length);
			// write(1, e->message, e->nb_blocks * 8);
	}
}
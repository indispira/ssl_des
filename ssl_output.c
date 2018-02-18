/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:13:39 by sboulet           #+#    #+#             */
/*   Updated: 2018/02/18 23:03:16 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_ssl_des.h"

static void	ssl_output_base64(t_env *e, int fd)
{
	int i;

	i = 0;
	while (i < e->length)
	{
		write(fd, e->out + i, e->length - i > 63 ? 64 : e->length - i);
		write(fd, "\n", 1);
		i += 64;
	}
}

static void	ssl_output_file(t_env *e)
{
	int		fd;

	if ((fd = open(e->outfile, O_RDWR | O_CREAT, 0644)) == -1)
	{
		ft_putendl("Open of the input file has failed\n");
		ssl_free_env(e);
		exit(0);
	}
	if (e->flag & FLAG_E && !(e->flag & FLAG_O))
		ft_putendl_fd(e->out, fd);
	else
	{
		if (((e->cmd & B64) || (e->cmd & DES && e->flag & FLAG_A))
			&& !(e->flag & FLAG_D))
			ssl_output_base64(e, fd);
		else if (e->cmd & DES || (e->cmd & B64 && e->flag & FLAG_D))
		{
			printf("HERE\n");
			write(fd, e->out, e->length);
			// ft_putstr_fd(e->out + e->length - 8, fd);
		}
		else
			ft_putstr_fd(e->out, fd);
		// write(fd, e->out, e->nb_blocks * 8);
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
	if (e->flag & FLAG_O && !e->outfile)
		write(2, "Requires an outfile file.\n", 24);
	else if (e->flag & FLAG_O)
		ssl_output_file(e);
	else if (((e->flag & FLAG_E) || !(e->flag & FLAG_D)) && ((e->cmd & B64)
		|| (e->flag & FLAG_A)))
		ssl_output_base64(e, 1);
	// TODO implementation output des
	// else if (e->flag & FLAG_E)
	// {
	// 	write(1, e->out, e->length);
	// 	// write(1, e->out, e->nb_blocks * 8);
	// 	write(1, "\n", 1);
	// }
	else
	{
		if (e->cmd & B64)
			ft_putstr(e->out);
		else
			write(1, e->out, e->length);
			// write(1, e->out, e->nb_blocks * 8);
	}
}

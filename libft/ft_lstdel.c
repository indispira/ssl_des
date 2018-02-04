/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:09:25 by sboulet           #+#    #+#             */
/*   Updated: 2016/04/25 12:37:29 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*next;

	tmp = malloc(sizeof(t_list));
	next = malloc(sizeof(t_list));
	if ((*alst)->next)
		next = (*alst)->next;
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
	while (next)
	{
		tmp = next;
		if (next->next)
			next = next->next;
		else
			next = NULL;
		del(tmp->content, tmp->content_size);
		free(tmp);
	}
}

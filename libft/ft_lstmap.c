/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:13:32 by sboulet           #+#    #+#             */
/*   Updated: 2015/12/06 19:08:51 by sboulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	if (lst)
	{
		new = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (!new)
			return (NULL);
		new->next = NULL;
	}
	while (lst->next)
	{
		lst = lst->next;
		tmp = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (!tmp)
			return (NULL);
		new->next = tmp;
	}
	return (new);
}

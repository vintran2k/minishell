/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:59:24 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 15:47:36 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_dlist	*create_elem(void *data)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	push_back(t_dlist **lst, void *data)
{
	t_dlist	*tmp;
	t_dlist	*new;

	new = create_elem(data);
	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int	lst_len(t_dlist **lst)
{
	int		i;
	t_dlist	*tmp;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	lst_delone(t_dlist *lst)
{
	int	ret;

	ret = 0;
	if (!lst)
		return (0);
	if (lst->prev)
	{
		if (lst->next)
			lst->prev->next = lst->next;
		else
			lst->prev->next = NULL;
	}
	if (lst->next)
	{
		if (lst->prev)
			lst->next->prev = lst->prev;
		else
			lst->next->prev = NULL;
	}
	if (!lst->next && !lst->prev)
		ret = -1;
	if (lst->data)
		free(lst->data);
	free(lst);
	return (ret);
}

void	lst_clear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
	*lst = 0;
}

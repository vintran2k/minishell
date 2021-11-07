/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:59:24 by vintran           #+#    #+#             */
/*   Updated: 2021/11/07 01:47:58 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*create_elem(void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	push_back(t_list **lst, void *data)
{
	t_list	*tmp;
	t_list	*new;

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

void	push_front(t_list **lst, void *data)
{
	t_list	*new;

	new = create_elem(data);
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}

int	lst_len(t_list **lst)
{
	int		i;
	t_list	*tmp;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	lst_delone(t_list *lst)
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

void	lst_clear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
	*lst = 0;
}

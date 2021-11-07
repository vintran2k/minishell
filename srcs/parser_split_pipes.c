/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:12:06 by vintran           #+#    #+#             */
/*   Updated: 2021/11/07 17:57:56 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*fill_s(t_list **s, t_list *lst)
{
	*s = create_elem(ft_strndup((char *)lst->data,
				ft_strlen((char *)lst->data)));
	if (*s == NULL)
		return (malloc_error2());
	lst = lst->next;
	while (lst && ft_strcmp((char *)lst->data, "|"))
	{
		push_back(s, ft_strndup((char *)lst->data,
				ft_strlen((char *)lst->data)));
		lst = lst->next;
	}
	if (lst)
		lst = lst->next;
	return (lst);
}

t_list	**split_pipes(t_list *lst, int n_pipes)
{
	t_list	**s;
	int		i;

	s = malloc(sizeof(t_list *) * (n_pipes + 2));
	if (!s)
		return (malloc_error2());
	s[n_pipes + 1] = NULL;
	i = 0;
	while (i <= n_pipes)
	{
		lst = fill_s(&s[i], lst);
		i++;
	}
	return (s);
}

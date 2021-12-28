/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:12:06 by vintran           #+#    #+#             */
/*   Updated: 2021/12/28 13:54:40 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_pipes(t_dlist *lst, t_lexer *b)
{
	if (((char *)lst->data)[b->i] == '|')
	{
		if (!lst->next)
			return (-1);
		b->j = 0;
		while (((char *)lst->data)[b->i + b->j] == '|')
			b->j++;
		if (b->j >= 2)
			return (-1);
	}
	return (0);
}

int	pipes_errors(t_dlist *lst)
{
	t_dlist	*tmp;
	t_lexer	b;

	b.q = 1;
	b.dq = 1;
	tmp = lst;
	while (tmp)
	{
		b.i = 0;
		while (((char *)tmp->data)[b.i])
		{
			quote_maj(&b, ((char *)tmp->data)[b.i]);
			if (b.q == 1 && b.dq == 1)
				if (check_pipes(tmp, &b) == -1)
					return (-1);
			b.i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

t_dlist	*fill_s(t_dlist **s, t_dlist *lst)
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

t_dlist	**split_pipes(t_dlist *lst, int n_pipes)
{
	t_dlist	**s;
	int		i;

	if (pipes_errors(lst) == -1)
	{
		ft_putstr_fd("minishell: syntax error unexpected token '|'\n",
			STDERR_FILENO);
		return (NULL);
	}
	s = malloc(sizeof(t_dlist *) * (n_pipes + 2));
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

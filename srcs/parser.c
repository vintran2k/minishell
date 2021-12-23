/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:27:03 by vintran           #+#    #+#             */
/*   Updated: 2021/12/23 15:39:38 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	count_pipes(t_dlist *lst)
{
	int	ret;

	ret = 0;
	while (lst)
	{
		if (!ft_strcmp(lst->data, "|"))
			ret++;
		lst = lst->next;
	}
	return (ret);
}

int	init_parser(t_mini *m, t_dlist *lst)
{
	int	i;

	m->s = NULL;
	m->in = NULL;
	m->out = NULL;
	m->n_pipes = count_pipes(lst);
	m->s = split_pipes(lst, m->n_pipes);
	if (!m->s)
		return (-1);
	m->in = malloc(sizeof(t_dlist *) * (m->n_pipes + 1));
	if (!m->in)
		return (malloc_error());
	m->out = malloc(sizeof(t_dlist *) * (m->n_pipes + 1));
	if (!m->out)
		return (malloc_error());
	i = 0;
	while (i <= m->n_pipes)
	{
		m->in[i] = NULL;
		m->out[i++] = NULL;
	}
	return (0);
}

int	parser(t_dlist **lst, t_mini *m)
{
	if (init_parser(m, *lst) == -1)
	{
		free_mini_struct(m);
		return (-1);
	}
	if (get_redirections(m) == -1 || remove_quotes(m) == -1)
	{
		free_mini_struct(m);
		return (-1);
	}
	return (0);
}

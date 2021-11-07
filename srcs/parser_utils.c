/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:33:41 by vintran           #+#    #+#             */
/*   Updated: 2021/11/07 17:14:49 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	init_parser(t_mini *m, t_list *lst)
{
	m->s = NULL;
	m->in = NULL;
	m->out = NULL;
	m->n_pipes = count_pipes(lst);
	m->s = split_pipes(lst, m->n_pipes);
	if (!m->s)
		return (-1);
	m->in = malloc(sizeof(t_list *) * (m->n_pipes + 1));
	if (!m->in)
		return (malloc_error());
	m->out = malloc(sizeof(t_list *) * (m->n_pipes + 1));
	if (!m->out)
		return (malloc_error());
	return (0);
}

int	count_pipes(t_list *lst)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:46:26 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 15:48:03 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	get_redir_type(t_dlist *lst, char *redir)
{
	while (lst->next)
		lst = lst->next;
	lst->type = 1;
	if (!ft_strcmp(redir, ">>"))
		lst->type = 2;
	else if (!ft_strcmp(redir, "<<"))
		lst->type = 2;
}

int	fill_redirections_lst(t_mini *m, t_dlist *tmp, int i)
{
	if (redirections_error(tmp) == -1)
	{
		g_vars.error = 2;
		return (-1);
	}
	if (((char *)tmp->data)[0] == '<')
	{
		push_back(&m->in[i], ft_strndup((char *)tmp->next->data,
				ft_strlen((char *)tmp->next->data)));
		get_redir_type(m->in[i], (char *)tmp->data);
	}
	if (((char *)tmp->data)[0] == '>')
	{
		push_back(&m->out[i], ft_strndup((char *)tmp->next->data,
				ft_strlen((char *)tmp->next->data)));
		get_redir_type(m->out[i], (char *)tmp->data);
	}
	return (0);
}

t_dlist	*remove_redirections(t_dlist **begin, t_dlist *tmp)
{
	int		i;
	t_dlist	*rm;

	i = 0;
	rm = tmp;
	while (tmp && i++ < 2)
		tmp = tmp->next;
	if (rm == *begin)
		*begin = tmp;
	if (lst_delone(rm->next) == -1 || lst_delone(rm) == -1)
		*begin = NULL;
	return (tmp);
}

int	get_redirections(t_mini *m)
{
	int		i;
	t_dlist	*tmp;

	i = 0;
	while (i <= m->n_pipes)
	{
		m->in[i] = NULL;
		m->out[i] = NULL;
		tmp = m->s[i];
		while (tmp)
		{
			if (((char *)tmp->data)[0] == '>' || ((char *)tmp->data)[0] == '<')
			{
				if (fill_redirections_lst(m, tmp, i) == -1)
					return (-1);
				tmp = remove_redirections(&m->s[i], tmp);
			}
			else
				tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

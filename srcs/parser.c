/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:27:03 by vintran           #+#    #+#             */
/*   Updated: 2021/11/07 16:15:29 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

int	get_redirections(t_mini *m)		//	in progress
{
	int	i;
	t_list *tmp;

	i = 0;
	while (i < m->n_pipes + 1)
	{
		m->in[i] = NULL;
		m->out[i] = NULL;
		tmp = m->s[i];
		while (tmp)
		{
			
			if (((char *)tmp->data)[0] == '>' || ((char *)tmp->data)[0] == '<')
			{
				if (redirections_error(tmp) == -1)
					return (-1);
				if (((char *)tmp->data)[0] == '<')
					push_back(&m->in[i], ft_strndup((char *)tmp->next->data, ft_strlen((char *)tmp->next->data)));
				if (((char *)tmp->data)[0] == '>')
					push_back(&m->out[i], ft_strndup((char *)tmp->next->data, ft_strlen((char *)tmp->next->data)));
				int a = 0;
				t_list	*rm;
				rm = tmp;
				while (tmp && a++ < 2)
					tmp = tmp->next;
				if (rm == m->s[i])
					m->s[i] = tmp;
				if (lst_delone(rm->next) == -1 || lst_delone(rm) == -1)
					m->s[i] = NULL;
			}
			else
				tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

int	init_parser(t_mini *m, t_list *lst)
{
	m->n_pipes = count_pipes(lst);
	m->s = split_pipes(lst, m->n_pipes);
	m->in = malloc(sizeof(t_list *) * (m->n_pipes + 1));
	if (!m->in)
		return (malloc_error());
	m->out = malloc(sizeof(t_list *) * (m->n_pipes + 1));
	if (!m->out)
		return (malloc_error());
	return (0);
}

int	parser(t_list **lst)		// in progress
{
	t_list	*tmp;
	t_mini	m;

	if (init_parser(&m, *lst) == -1)
	{
		free_mini_struct(&m);
		return (-1);
	}
	if (get_redirections(&m) == -1 || remove_quotes(&m) == -1)
	{
		free_mini_struct(&m);
		return (-1);
	}
	int i = 0;
	int j;
	while (i < m.n_pipes + 1)
	{
		j = 0;
		tmp = m.s[i];
		while (tmp)
		{
			printf("[%d] --> [%d] = |%s|\n", i, j, (char *)tmp->data);
			tmp = tmp->next;
			j++;
		}
		if (m.in[i])
		{
			tmp = m.in[i];
			while (tmp)
			{
				printf("in -> %s\n", (char *)tmp->data);
				tmp = tmp->next;
			}
		}
		if (m.out[i])
		{
			tmp = m.out[i];
			while (tmp)
			{
				printf("out -> %s\n", (char *)tmp->data);
				tmp = tmp->next;
			}
		}
		i++;
	}
	free_mini_struct(&m);
	return (0);		//
}
// > ok ok > ok ok | < ok > oue | sjkjd -dklcs > asdk < sijd <ijads aslkj | isjd >siod asdh<adh
// a recoder au propre au niveau des listes chainees
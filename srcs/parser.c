/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:27:03 by vintran           #+#    #+#             */
/*   Updated: 2021/11/06 17:56:48 by vintran          ###   ########.fr       */
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

/*int	parse_redirections(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		
	}
}*/

int	get_redirections(t_mini *m)		//	in progress
{
	int	i;
	t_list *tmp;

	i = 0;
	while (m->s[i])
	{
		tmp = m->s[i];
		while (tmp)
		{
			if (((char *)tmp->data)[0] == '>' || ((char *)tmp->data)[0] == '<')
			{
				if (redirections_error((char *)tmp->data) == -1)
					return (-1);
				//	maj_redirections to do
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

int	parser(t_list **lst)		// in progress
{
	t_list	*tmp;
	t_mini	m;

	tmp = *lst;
	m.n_pipes = count_pipes(*lst);
	m.s = split_pipes(*lst, m.n_pipes);
	if (get_redirections(&m) == -1 || remove_quotes(m.s) == -1)
	{
		free_mini_struct(&m);
		return (-1);
	}
	int i = 0;
	int j;
	while (m.s[i])
	{
		j = 0;
		t_list *tmp = m.s[i];
		while (tmp)
		{
			printf("[%d] --> [%d] = |%s|\n", i, j, (char *)tmp->data);
			tmp = tmp->next;
			j++;
		}
		i++;
	}
	free_mini_struct(&m);
	return (0);		//
}

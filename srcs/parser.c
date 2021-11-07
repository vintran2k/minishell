/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:27:03 by vintran           #+#    #+#             */
/*   Updated: 2021/11/07 17:56:24 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
				printf("in -> %d = %s\n", tmp->type, (char *)tmp->data);
				tmp = tmp->next;
			}
		}
		if (m.out[i])
		{
			tmp = m.out[i];
			while (tmp)
			{
				printf("out -> %d = %s\n", tmp->type, (char *)tmp->data);
				tmp = tmp->next;
			}
		}
		i++;
	}
	free_mini_struct(&m);
	return (0);		//
}
// > ok ok > ok ok | < ok > oue | sjkjd -dklcs > asdk < sijd <ijads aslkj | isjd >siod asdh<adh
// > ok ok >> ok "ok" | < ok > "oue" | sjkjd -dklcs >> 'asdk' < sijd <<ijads aslkj | isjd >siod "asdh"<<adh
// a recoder au propre au niveau des listes chainees
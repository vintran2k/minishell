/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_remove_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:14:06 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 15:48:10 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*create_new_str(char *s)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	remove_lst_quotes(t_dlist *lst)
{
	char	*new;

	while (lst)
	{
		new = create_new_str((char *)lst->data);
		if (!new)
			return (malloc_error());
		free(lst->data);
		lst->data = new;
		lst = lst->next;
	}
	return (0);
}

int	remove_quotes(t_mini *m)
{
	int		i;

	i = 0;
	while (i <= m->n_pipes)
	{
		if (remove_lst_quotes(m->s[i]) == -1)
			return (-1);
		if (remove_lst_quotes(m->in[i]) == -1)
			return (-1);
		if (remove_lst_quotes(m->out[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

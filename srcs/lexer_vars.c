/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:10:20 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 13:25:09 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	replace_var(t_list **lst, char *env, int dq)
{
	int		i;
	int		newlen;
	char	*new;
	t_list	*tmp;

	tmp = *lst;
	i = 0;
	while (((char *)tmp->data)[i] != '$')
		i++;
	newlen = get_newlen((char *)tmp->data, env, dq);
	new = malloc(newlen + 1);
	if (!new)
		return (malloc_error());
	fill_new(new, tmp->data, env, i);
	free(tmp->data);
	if (dq == -1)
		new[newlen - 1] = '"';
	new[newlen] = '\0';
	tmp->data = new;
	return (0);
}

int	remove_var(t_list *var, int i)
{
	int		j;
	int		len;
	char	*new;

	if (!ft_isalnum(((char *)var->data)[i + 1]))
		return (i);
	j = var_len(&((char *)var->data)[i]);
	len = i + ft_strlen(&((char *)var->data)[i + j]);
	new = malloc(len + 1);
	new[0] = '\0';
	ft_strncat(new, var->data, len);
	new[i] = '\0';
	ft_strncat(&new[i], &((char *)var->data)[i + j], len - i);
	free(var->data);
	var->data = new;
	return (i - 1);
}

void	remove_empties(t_lexer *a)
{
	t_list	*tmp;
	t_list	*del;

	tmp = a->lst;
	while (tmp)
	{
		if (!((char *)tmp->data)[0])
		{
			del = tmp;
			tmp = tmp->next;
			if (del == a->lst)
				a->lst = tmp;
			lst_delone(del);
		}
		else if (tmp)
			tmp = tmp->next;
	}
}

void	parse_vars(t_lexer *a)
{
	t_list	*tmp;
	char	*env;

	tmp = a->lst;
	while (tmp)
	{
		a->i = -1;
		while (((char *)tmp->data)[++a->i])
		{
			quote_maj(a, ((char *)tmp->data)[a->i]);
			if (((char *)tmp->data)[a->i] == '$' && a->q == 1)
			{
				env = is_in_env(&((char *)tmp->data)[a->i]);
				if (env || ft_strncmp(&((char *)tmp->data)[a->i], "$?", 2) == 0)
				{
					replace_var(&tmp, env, a->dq);
					a->i = 0;
				}
				else
					a->i = remove_var(tmp, a->i);
			}
		}
		tmp = tmp->next;
	}
	remove_empties(a);
}

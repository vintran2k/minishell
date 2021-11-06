/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:33:41 by vintran           #+#    #+#             */
/*   Updated: 2021/11/06 17:58:14 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
		if (!(s[i] == '\'' || s[i] == '\"'))
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	remove_quotes(t_list **s)
{
	char	*new;
	int		i;
	t_list	*tmp;

	i = 0;
	while (s[i])
	{
		tmp = s[i];
		while (tmp)
		{
			new = create_new_str((char *)tmp->data);
			if (!new)
				return (malloc_error());
			free(tmp->data);
			tmp->data = new;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

int	count_cmd_strs(t_list *lst)
{
	int	ret;

	ret = 0;
	while (lst)
	{
		if (!ft_strcmp((char *)lst->data, "|"))
			return (ret);
		lst = lst->next;
		ret++;
	}
	return (ret);
}

t_list	*fill_s(t_list **s, t_list *lst)
{
	*s = create_elem(ft_strndup((char *)lst->data, ft_strlen((char *)lst->data)));
	if (*s == NULL)
		return (malloc_error2());
	lst = lst->next;
	while (lst && ft_strcmp((char *)lst->data, "|"))
	{
		push_back(s, ft_strndup((char *)lst->data, ft_strlen((char *)lst->data)));
		lst = lst->next;
	}
	if (lst)
		lst = lst->next;
	return (lst);
}

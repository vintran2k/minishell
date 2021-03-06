/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:37:32 by vintran           #+#    #+#             */
/*   Updated: 2021/12/23 15:36:13 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_strndup(char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && i < n)
		i++;
	dest = malloc(sizeof(*dest) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	add_str_list(t_dlist **lst, char *line, int len)
{
	char	*data;

	data = ft_strndup(line, len);
	if (!data)
		return ;
	push_back(lst, data);
}

void	lexer(char *line, t_lexer *a)
{
	while (line[a->i])
	{
		a->j = 0;
		while (line[a->i + a->j] && ft_strchr(a->sep, line[a->i + a->j]))
			a->j++;
		if (a->j)
			add_str_list(&(a->lst), &line[a->i], a->j);
		a->i += a->j;
		while (line[a->i] == ' ' && a->q == 1 && a->dq == 1)
			a->i++;
		a->j = 0;
		while (line[a->i + a->j] && ((!ft_strchr(a->sep, line[a->i + a->j])
					&& line[a->i + a->j] != ' ' && a->q == 1
					&& a->dq == 1) || (a->q != 1 || a->dq != 1)))
		{
			quote_maj(a, line[a->i + a->j]);
			a->j++;
		}
		if (a->j)
			add_str_list(&(a->lst), &line[a->i], a->j);
		a->i += a->j;
	}
	if (!is_quote_closed(a))
		lst_clear(&(a->lst), &free);
	parse_vars(a);
}

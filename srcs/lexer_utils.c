/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:40:28 by vintran           #+#    #+#             */
/*   Updated: 2021/11/07 18:00:03 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	quote_maj(t_lexer *a, char c)
{
	if (c == '\'' && a->dq == 1)
	{
		a->q *= -1;
		return (1);
	}
	else if (c == '\"' && a->q == 1)
	{
		a->dq *= -1;
		return (1);
	}
	return (0);
}

int	is_quote_closed(t_lexer *a)
{
	if (a->q != 1)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `\'\'\n", STDERR_FILENO);
		return (0);
	}
	if (a->dq != 1)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `\"\'\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	init_lexer(t_lexer *a)
{
	a->i = 0;
	a->q = 1;
	a->dq = 1;
	a->sep = "<>|";
	a->lst = NULL;
}

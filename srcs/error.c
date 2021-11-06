/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:08:21 by vintran           #+#    #+#             */
/*   Updated: 2021/11/04 17:49:46 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	malloc_error(void)
{
	perror("minishell");
	return (-1);
}

void	*malloc_error2(void)
{
	perror("minishell");
	return (NULL);
}

int	print_redirections_error(char c)
{
	char	s[4];

	s[0] = c;
	s[1] = '\'';
	s[2] = '\n';
	s[3] = '\0';
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	return (-1);
}

int		redirections_error(char *s)
{
	int		i;

	i = 1;
	while (s[i])
	{
		if (s[i] != s[0])
			return (print_redirections_error(s[i]));
		if (i == 2)
			return (print_redirections_error(s[i]));
		i++;
	}
	return (0);
}

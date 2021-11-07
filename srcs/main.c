/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:19:15 by vintran           #+#    #+#             */
/*   Updated: 2021/11/07 17:53:23 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	parsing_line(char *line)
{
	t_lexer	a;

	init_lexer(&a);
	if (!lexer(line, &a))
		return (-1);
	if (parser(&(a.lst)) == -1)
	{
		lst_clear(&(a.lst), &free);
		return (-1);
	}
	lst_clear(&(a.lst), &free);
	//	executor()
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	while ((line = readline("$ ")))
	{
		parsing_line(line);
		free(line);
	}
	return (0);
}

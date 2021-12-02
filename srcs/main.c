/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:19:15 by vintran           #+#    #+#             */
/*   Updated: 2021/12/02 15:16:13 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	parsing_line(char *line, char **env)
{
	t_lexer	a;
	t_mini	m;

	init_lexer(&a);
	if (!lexer(line, &a))
		return (-1);
	if (parser(&(a.lst), &m) == -1)
	{
		lst_clear(&(a.lst), &free);
		return (-1);
	}
	lst_clear(&(a.lst), &free);
	if (executor(&m, env) == -1)
		return (-1);
	free_mini_struct(&m);
	return (0);
}

void	signal_error(int signal)
{
	(void)signal;
	write(1, "\n$ ", 3);
	g_vars.g_error = 1;
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_error);
		line = readline("$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(line);
		parsing_line(line, env);
		free(line);
		fprintf(stderr, "g_error = %d\n", g_vars.g_error);
	}
	rl_clear_history();
	return (0);
}

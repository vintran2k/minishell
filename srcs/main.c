/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:19:15 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 17:02:32 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_dlist	*get_env(char **env)
{
	t_dlist	*lst;
	int		i;

	lst = NULL;
	i = 0;
	while (env[i])
		push_back(&lst, ft_strdup(env[i++]));
	return (lst);
}

int	parsing_line(char *line, char **env)
{
	t_lexer	a;
	t_mini	m;

	init_lexer(&a);
	lexer(line, &a);
	if (!a.lst)
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;

	(void)ac;
	(void)av;
	g_vars.env = get_env(env);
	while (1)
	{
		prompt = get_prompt(0);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_main);
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(line);
		parsing_line(line, env);
		free(line);
	}
	lst_clear(&g_vars.env, &free);
	rl_clear_history();
	return (g_vars.error);
}


//	unset toutes les var (peut etre pb avc lst_delone dans unset)
//	segfault --> rm -rf le dossier
//	leaks here_doc ^D --> env ou export
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:19:15 by vintran           #+#    #+#             */
/*   Updated: 2021/12/22 15:17:19 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#define ENV_FILE	"/tmp/minishell_env"
void	add_env_history(void)
{
	int	file = open(ENV_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	t_dlist	*tmp = g_vars.env;
	
	while (tmp)
	{
		ft_putendl_fd(tmp->data, file);
		ft_putendl_fd("\n", file);
		tmp = tmp->next;
	}
	close(file);
}

t_dlist	*get_env(char **env, int status)
{
	t_dlist	*lst;
	int		i;
	int		env_fd;

	lst = NULL;
	env_fd = open(ENV_FILE, O_RDONLY);
	if (env_fd != -1 && status == 1)
	{
		char	*line;
		int		ret = 1;

		while (ret)
		{
			ret = get_next_line(env_fd, &line);
			if ((status == 1 && line[0] != '_') || status == 0)
				push_back(&lst, line);
		}
		close(env_fd);
		return (lst);
	}
	i = 0;
	while (env[i])
	{
		if ((status == 1 && env[i][0] != '_') || status == 0)
			push_back(&lst, ft_strdup(env[i]));
		i++;
	}
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
	g_vars.env = get_env(env, 0);
	g_vars.export = get_env(env, 1);
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
		add_env_history();
		parsing_line(line, env);
		free(line);
	}
	lst_clear(&g_vars.env, &free);
	lst_clear(&g_vars.export, &free);
	rl_clear_history();
	unlink(ENV_FILE);
	return (g_vars.error);
}


//	unset toutes les var (peut etre pb avc lst_delone dans unset)
//	segfault --> rm -rf le dossier
//	leaks here_doc ^D --> env ou export
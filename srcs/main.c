/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:19:15 by vintran           #+#    #+#             */
/*   Updated: 2021/12/13 07:40:36 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*get_env(char **env)
{
	t_list	*lst;
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

char	*get_prompt(int arrow)
{
	char	*prompt;
	char	*cwd;
	int		i;

	if (g_vars.error == 0)
		printf("\033[1;32m➜ \033[0m");
	else
		printf("\033[1;31m➜ \033[0m");
	if (arrow == 1)
		return (NULL);
	cwd = getcwd(NULL, 0);
	i = ft_strlen(cwd) - 1;
	while (i > 0)
	{
		if (cwd[i - 1] == '/')
			break ;
		i--;
	}
	prompt = malloc(ft_strlen(&cwd[i]) + 16);	//
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strcat(prompt, "\033[1;34m");
	if (i == 1)
		ft_strcat(prompt, cwd);
	else
		ft_strcat(prompt, &cwd[i]);
	ft_strcat(prompt, " \033[0m");
	free(cwd);
	return (prompt);
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
		t_list *tmp = g_vars.env;
		while (tmp)
		{
			printf("%s\n", (char *)tmp->data);
			tmp = tmp->next;
		}
	}
	lst_clear(&g_vars.env, &free);
	rl_clear_history();
	return (0);
}


// unset toutes les var (peut etre pb avc lst_delone dans unset)
// segfault --> rm -rf le dossier
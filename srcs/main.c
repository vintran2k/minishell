/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:19:15 by vintran           #+#    #+#             */
/*   Updated: 2021/12/23 15:35:40 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_dlist	*mini_env(int status)
{
	char	*pwd;
	char	*cwd;
	t_dlist	*env;

	env = NULL;
	cwd = getcwd(NULL, 0);
	pwd = malloc(5 + ft_strlen(cwd));
	pwd[0] = '\0';
	ft_strcat(pwd, "PWD=");
	ft_strcat(pwd, cwd);
	push_back(&env, pwd);
	push_back(&env, ft_strdup("PATH=/bin"));
	if (!status)
		push_back(&env, ft_strdup("_=/usr/bin/env"));
	return (env);
}

t_dlist	*get_env(char **env, int status)
{
	t_dlist	*lst;
	int		i;

	lst = NULL;
	i = 0;
	if (!env[0])
		return (mini_env(status));
	while (env[i])
	{
		if ((status == 1 && env[i][0] != '_') || status == 0)
			push_back(&lst, ft_strdup(env[i]));
		i++;
	}
	return (lst);
}

int	parsing_line(char *line)
{
	t_lexer	a;
	t_mini	m;

	init_lexer(&a);
	lexer(line, &a);
	/*t_dlist *lex = a.lst;
	while (lex)
	{
		printf("lex = |%s|\n", lex->data);
		lex = lex->next;
	}
	printf("\n\n");*/
	if (!a.lst)
		return (-1);
	if (parser(&(a.lst), &m) == -1)
	{
		lst_clear(&(a.lst), &free);
		return (-1);
	}
	lst_clear(&(a.lst), &free);
	/*t_dlist **s = m.s;
	int  i = 0;
	while (s[i])
	{
		t_dlist *si = s[i];
		while (si)
		{
			printf("|%s|\n", si->data);
			si = si->next;
		}
		i++;
	}*/
	if (executor(&m) == -1)
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
		parsing_line(line);
		free(line);
	}
	lst_clear(&g_vars.env, &free);
	lst_clear(&g_vars.export, &free);
	rl_clear_history();
	return (g_vars.error);
}

//	echo ||| ou cmd | --> erreur de parsing des pipes
//	echo -n -n lala
//	echo ${USER} :(
//	! ./minishell dans minishell --> ^C (signaux dans sigint fork)
//	SHLVL
//	env -i ./minishell
//	unset PATH, cmd --> pas de msg d'erreur cmd not found
//	unset toutes les var (peut etre pb avc lst_delone dans unset)
//	segfault --> rm -rf le dossier
//	leaks here_doc ^D --> env ou export
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:39:07 by vintran           #+#    #+#             */
/*   Updated: 2021/12/03 20:01:40 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	execve_error(t_exec *e)
{
	ft_putstr_fd("execve error a gerer\n", STDERR_FILENO);
	exit (1);
}

void	quit_forking(t_exec *e)
{
	close_fd(e, e->i);
	free_exec_struct(e, 0);
	if (e->infile && e->infile != -1)
	{
		close(e->infile);
		e->infile = 0;
	}
	if (e->outfile && e->outfile != -1)
	{
		close(e->outfile);
		e->outfile = 0;
	}
}

int	forking(char **env, t_mini *m, t_exec *e)
{
	e->ret = init_forking(m, e);
	if (e->ret == -1)
			perror("minishell");
	if (e->ret == 0)
	{
		signal(SIGINT, sigint_fork);
		signal(SIGQUIT, sigquit_fork);
		e->pid[e->i] = fork();
		if (e->pid[e->i] == 0)
		{
			rl_clear_history();
			if (e->i == 0)
				e->ret = first_fork(env, e);
			else if (e->i == e->pipes)
				e->ret = last_fork(env, e);
			else
				e->ret = mid_fork(env, e, e->i);
		}
	}
	quit_forking(e);
	return (e->ret);
}

void	forking_loops(t_mini *m, t_exec *e, char **env)
{
	printf("i = %d\n", e->i);
	while (e->i <= m->n_pipes)
	{
		if (forking(env, m, e) == -1)
			g_vars.g_error = 1;
		if (e->ret == 0)
			e->fork[e->i] = 1;
		if (e->ret == -130)
		{
			write(1, "\n", 1);
			break ;
		}
		e->i++;
	}
	e->i = 0;
	while (e->i <= e->pipes)
	{
		if (e->fork[e->i])
		{
			waitpid(e->pid[e->i], &e->status, 0);
			if (WIFEXITED(e->status))
				g_vars.g_error = WEXITSTATUS(e->status);
		}
		e->i++;
	}
}

int	executor(t_mini *m, char **env)
{
	t_exec	e;

	if (init_exec(&e, m, env) == -1)
	{
		free_exec_struct(&e, 1);
		return (-1);
	}
	forking_loops(m, &e, env);
	free_exec_struct(&e, 1);
	return (0);
}
//$ ls^C
//$ ^C -> ctrl D

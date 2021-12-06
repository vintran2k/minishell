/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:50:43 by vintran           #+#    #+#             */
/*   Updated: 2021/12/06 12:46:02 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	first_fork(char **env, t_exec *e)
{
	if (e->infile && e->infile != -1)
		dup2(e->infile, STDIN_FILENO);
	if (e->outfile && e->outfile != -1)
		dup2(e->outfile, STDOUT_FILENO);
	else if (e->pipes)
		dup2(e->fd[0][1], STDOUT_FILENO);
	close_first(e);
	if (execve(e->strs[0], e->strs, env) == -1)
		execve_error(e);
	return (0);
}

int	mid_fork(char **env, t_exec *e, int i)
{
	if (e->infile && e->infile != -1)
		dup2(e->infile, STDIN_FILENO);
	else
		dup2(e->fd[i - 1][0], STDIN_FILENO);
	if (e->outfile && e->outfile != -1)
		dup2(e->outfile, STDOUT_FILENO);
	else
		dup2(e->fd[i][1], STDOUT_FILENO);
	close_mid(e, i);
	if (execve(e->strs[0], e->strs, env) == -1)
		execve_error(e);
	return (0);
}

int	last_fork(char **env, t_exec *e)
{
	if (e->infile && e->infile != -1)
		dup2(e->infile, STDIN_FILENO);
	else
		dup2(e->fd[e->pipes - 1][0], STDIN_FILENO);
	if (e->outfile && e->outfile != -1)
		dup2(e->outfile, STDOUT_FILENO);
	close_last(e);
	if (execve(e->strs[0], e->strs, env) == -1)
		execve_error(e);
	return (0);
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

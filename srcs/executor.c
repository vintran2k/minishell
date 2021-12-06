/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:39:07 by vintran           #+#    #+#             */
/*   Updated: 2021/12/06 13:27:37 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	execve_error(t_exec *e)
{
	ft_putstr_fd("execve error a gerer\n", STDERR_FILENO);
	exit (1);
}

int	malloc_pipes(t_exec *e)
{
	int	i;

	i = 0;
	while (i < e->pipes)
	{
		e->fd[i] = malloc(sizeof(int) * 2);
		if (!e->fd[i])
			return (malloc_error());
		if (pipe(e->fd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_exec(t_exec *e, t_mini *m, char **env)
{
	ft_bzero(e, sizeof(t_exec));
	e->pipes = m->n_pipes;
	e->path = get_env_path(env);
	if (!e->path)
		return (-1);
	e->pid = malloc(sizeof(pid_t) * (e->pipes + 1));
	if (!e->pid)
		return (malloc_error());
	if (e->pipes)
	{
		e->fd = malloc(sizeof(int *) * e->pipes);
		if (!e->fd)
			return (malloc_error());
	}
	if (malloc_pipes(e) == -1)
		return (-1);
	return (0);
}

void	forking_loops(t_mini *m, t_exec *e, char **env)
{
	while (e->i <= m->n_pipes)
	{
		if (forking(env, m, e) == -1)
			g_vars.g_error = 1;
		if (e->ret == 0)
		{
			waitpid(e->pid[e->i], &e->status, 0);
			if (WIFEXITED(e->status))
				g_vars.g_error = WEXITSTATUS(e->status);
		}
		if (e->ret == -130)
		{
			write(1, "\n", 1);
			break ;
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

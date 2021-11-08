/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:39:07 by vintran           #+#    #+#             */
/*   Updated: 2021/11/08 17:07:31 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**get_env_path(char **env)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			res = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (res);
}

int		init_exec(t_exec *e, t_mini *m, char **env)
{
	int	i;

	e->pipes = m->n_pipes;
	e->path = get_env_path(env);
	if (!e->path)
		return (-1);
	e->fork = malloc(sizeof(int) * (e->pipes + 1));
	if (!e->fork)
		return (malloc_error());
	e->pid = malloc(sizeof(pid_t) * (e->pipes + 1));
	if (!e->pid)
		return (malloc_error());
	e->fd = malloc(sizeof(int *) * e->pipes);
	if (!e->fd)
		return (malloc_error());
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
}

int	executor(t_mini *m, char **env)
{
	t_exec	e;
	int		i;

	if (init_exec(&e, m, env) == -1)
	{
		//free_exec_struct(&e);
		return (-1);
	}
	i = 0;
	while (i <= m->n_pipes)
	{
		//forking();
		if (e.ret == 0)
			e.fork[i] = 1;
		else
			e.fork[i] = 0;
		i++;
	}
	i = 0;
	while (i <= e.pipes)
	{
		if (e.fork[i])
		{
			waitpid(e.pid[i], &e.status, 0);
			if (WIFEXITED(e.status))
				e.exit = WEXITSTATUS(e.status);
		}
		i++;
	}
	//free
}

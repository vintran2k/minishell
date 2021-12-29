/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:43:32 by vintran           #+#    #+#             */
/*   Updated: 2021/12/28 16:39:05 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

int	init_exec(t_exec *e, t_mini *m)
{
	ft_bzero(e, sizeof(t_exec));
	e->pipes = m->n_pipes;
	e->pid = malloc(sizeof(pid_t) * (e->pipes + 1));
	if (!e->pid)
		return (malloc_error());
	e->forks = malloc(sizeof(int) * (e->pipes + 1));
	if (!e->forks)
		return (malloc_error());
	ft_bzero(e->forks, sizeof(int));
	e->env = lst_to_char(g_vars.env);
	e->path = get_env_path(e->env);
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

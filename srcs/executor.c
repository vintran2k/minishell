/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:39:07 by vintran           #+#    #+#             */
/*   Updated: 2021/11/09 17:45:56 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
	return (0);
}

int	init_forking(t_mini *m, t_exec *e)
{
	int	lstlen;
	int	i;
	
	i = 0;
	while (m->in && m->in[i])
	{
		e->infile = open((char *)m->in[i]->data, O_RDONLY);		//	<< a gerer
		if (e->infile == -1)
			return (-1);
		i++;
	}
	i = 0;
	while (m->out && m->out[i])
	{
		e->outfile = open((char *)m->out[i]->data, O_WRONLY | O_CREAT | O_TRUNC, 0664); 	//	>> a gerer
		if (e->outfile == -1)
			return (-1);
		i++;
	}
	lstlen = lst_len(&m->s[e->i]);
	if (lstlen == 0)
		return (-1);
	return (0);
}

int	forking(t_mini *m, t_exec *e)
{
	return (0);
}

int	executor(t_mini *m, char **env)
{
	t_exec	e;

	if (init_exec(&e, m, env) == -1)
	{
		//free_exec_struct(&e);
		return (-1);
	}
	e.i = 0;
	while (e.i <= m->n_pipes)
	{
		forking(m, &e);
		/*if (e.ret == 0)
			e.fork[i] = 1;
		else
			e.fork[i] = 0;*/
		e.i++;
	}
	e.i = 0;
	/*while (e.i <= e.pipes)
	{
		if (e.fork[e.i])
		{
			waitpid(e.pid[e.i], &e.status, 0);
			if (WIFEXITED(e.status))
				e.exit = WEXITSTATUS(e.status);
		}
		e.i++;
	}*/
	//free
	return (0);
}

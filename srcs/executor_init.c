/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:35:42 by vintran           #+#    #+#             */
/*   Updated: 2021/12/03 17:19:44 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		init_exec(t_exec *e, t_mini *m, char **env)
{
	int	i;

	ft_bzero(e, sizeof(t_exec));
	e->pipes = m->n_pipes;
	e->path = get_env_path(env);
	if (!e->path)
		return (-1);
	e->fork = malloc(sizeof(int) * (e->pipes + 1));
	if (!e->fork)
		return (malloc_error());
	for (int a = 0; a <= e->pipes; a++)
		e->fork[a] = 0;
	e->pid = malloc(sizeof(pid_t) * (e->pipes + 1));
	if (!e->pid)
		return (malloc_error());
	if (e->pipes)
	{
		e->fd = malloc(sizeof(int *) * e->pipes);
		if (!e->fd)
			return (malloc_error());
	}
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

int	open_files(t_mini *m, t_exec *e)
{
	t_list	*tmp;

	tmp = m->in[e->i];
	while (tmp)
	{
		if (tmp->type == 1)
			e->infile = open((char *)tmp->data, O_RDONLY);
		if (e->infile == -1)
			return (-1);
		if (tmp->type == 2)
		{
			g_vars.g_eof = ft_strdup((char *)tmp->data);
			e->infile = here_doc(e, m);
			free(g_vars.g_eof);
		}
		if (e->infile == -1)
			return (-1);
		if (g_vars.g_error == 130)
			return (-130);
		tmp = tmp->next;
	}
	tmp = m->out[e->i];
	while (tmp)
	{
		if (tmp->type == 1)
			e->outfile = open((char *)tmp->data, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp->type == 2)
			e->outfile = open((char *)tmp->data, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (e->outfile == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	init_forking(t_mini *m, t_exec *e)
{
	int		lstlen;
	t_list	*tmp;
	int		i;

	//g_vars.g_error = 0;
	i = open_files(m, e);
	if (i < 0)
		return (i);
	lstlen = lst_len(&m->s[e->i]);
	if (lstlen == 0)
		return (-2);	//pas de cmds
	e->cmdpath = get_cmdpath((char *)m->s[e->i]->data, e->path);
	e->strs = malloc(sizeof(char *) * (lstlen + 1));
	e->strs[lstlen] = NULL;
	i = 0;
	tmp = m->s[e->i];
	e->strs[0] = e->cmdpath;
	if (e->strs[0])
	{
		i = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		e->strs[i++] = (char *)tmp->data;
		tmp = tmp->next;
	}
	return (0);
}

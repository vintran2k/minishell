/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:50:56 by vintran           #+#    #+#             */
/*   Updated: 2021/12/22 16:11:19 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_mini_struct(t_mini *m)
{
	int		i;

	i = 0;
	while (i <= m->n_pipes)
	{
		if (m->s && m->s[i])
			lst_clear(&m->s[i], &free);
		if (m->in && m->in[i])
			lst_clear(&m->in[i], &free);
		if (m->out && m->out[i])
			lst_clear(&m->out[i], &free);
		i++;
	}
	if (m->s)
		free(m->s);
	if (m->in)
		free(m->in);
	if (m->out)
		free(m->out);
}

void	free_exec_struct(t_exec *e, int finish)
{
	int	i;

	if (e->cmdpath)
		free(e->cmdpath);
	if (e->strs)
		free(e->strs);
	if (e->env)
		free_strs(e->env);
	e->cmdpath = NULL;
	e->strs = NULL;
	e->env = NULL;
	if (finish)
	{
		free_strs(e->path);
		if (e->pid)
			free(e->pid);
		i = 0;
		while (i < e->pipes && e->fd && e->fd[i])
			free(e->fd[i++]);
		free(e->fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:39:07 by vintran           #+#    #+#             */
/*   Updated: 2021/12/29 15:06:30 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	exec_builtins(t_mini *m, t_exec *e)
{
	int	ret;

	if (e->builtin == 1)
		ret = echo(m->s[e->i]);
	if (e->builtin == 2)
		ret = cd(m->s[e->i]);
	if (e->builtin == 3)
		ret = pwd();
	if (e->builtin == 4)
		ret = export(m->s[e->i]);
	if (e->builtin == 5)
		ret = unset(m->s[e->i]);
	if (e->builtin == 6)
		ret = print_env();
	if (e->builtin == 7)
		ret = ft_exit(m->s[e->i], m, e);
	if (e->pipes || m->in[0] || m->out[0])
	{
		lst_clear(&g_vars.env, &free);
		lst_clear(&g_vars.export, &free);
		free_mini_struct(m);
		free_exec_struct(e, 1);
		exit (ret);
	}
	return (ret);
}

int	is_builtin(t_mini *m, t_exec *e)
{
	if (!m->s[e->i])
		return (0);
	if (!strcmp((char *)m->s[e->i]->data, "echo"))
		return (1);
	else if (!strcmp((char *)m->s[e->i]->data, "cd"))
		return (2);
	else if (!strcmp((char *)m->s[e->i]->data, "pwd"))
		return (3);
	else if (!strcmp((char *)m->s[e->i]->data, "export"))
		return (4);
	else if (!strcmp((char *)m->s[e->i]->data, "unset"))
		return (5);
	else if (!strcmp((char *)m->s[e->i]->data, "env"))
		return (6);
	else if (!strcmp((char *)m->s[e->i]->data, "exit"))
		return (7);
	return (0);
}

void	wait_childs(t_exec *e)
{
	e->i = 0;
	while (e->i <= e->pipes)
	{
		if (e->forks[e->i] == 1)
		{
			waitpid(e->pid[e->i], &e->status, 0);
			if (WIFEXITED(e->status))
				g_vars.error = WEXITSTATUS(e->status);
		}
		g_vars.pid = 0;
		e->i++;
	}
}

void	forking_loops(t_mini *m, t_exec *e)
{
	while (e->i <= m->n_pipes)
	{
		e->builtin = is_builtin(m, e);
		if (e->builtin && e->pipes == 0 && !m->in[0] && !m->out[0])
		{
			g_vars.error = exec_builtins(m, e);
			return ;
		}
		if (forking(m, e) == -1)
			g_vars.error = 1;
		if (e->ret == 0)
			e->forks[e->i] = 1;
		if (e->ret == -130)
			break ;
		e->i++;
	}
	wait_childs(e);
}

int	executor(t_mini *m)
{
	t_exec	e;

	if (init_exec(&e, m) == -1)
	{
		free_exec_struct(&e, 1);
		return (-1);
	}
	forking_loops(m, &e);
	free_exec_struct(&e, 1);
	return (0);
}

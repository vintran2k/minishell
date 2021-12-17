/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:39:07 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 12:51:13 by vintran          ###   ########.fr       */
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
	//...
	if (e->pipes)
	{
		lst_clear(&g_vars.env, &free);
		free_mini_struct(m);
		free_exec_struct(e, 1);
		exit (ret);
	}
	return (ret);
}

int	is_builtin(t_mini *m, t_exec *e)
{
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

void	forking_loops(t_mini *m, t_exec *e, char **env)
{
	while (e->i <= m->n_pipes)
	{
		e->builtin = is_builtin(m, e);
		if (e->builtin && e->pipes == 0)
		{
			g_vars.error = exec_builtins(m, e);
			return ;
		}
		if (forking(env, m, e) == -1)
			g_vars.error = 1;
		if (e->ret == 0)
		{
			waitpid(e->pid[e->i], &e->status, 0);
			if (WIFEXITED(e->status))
				g_vars.error = WEXITSTATUS(e->status);
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

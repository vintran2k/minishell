/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:50:43 by vintran           #+#    #+#             */
/*   Updated: 2021/12/02 13:55:51 by vintran          ###   ########.fr       */
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

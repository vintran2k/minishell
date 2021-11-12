/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:19:08 by vintran           #+#    #+#             */
/*   Updated: 2021/11/12 16:27:54 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	close_first(t_exec *e)
{
	int	i;
	int	j;

	if (!e->pipes)
		return ;
	i = 0;
	while (i < e->pipes)
	{
		j = 0;
		while (j < 2)
		{
			if (i != 0 || j != 1)
				close(e->fd[i][j]);
			j++;
		}
		i++;
	}
}

void	close_mid(t_exec *e, int index)
{
	int	i;
	int	j;

	if (!e->pipes)
		return ;
	i = 0;
	while (i < e->pipes)
	{
		j = 0;
		while (j < 2)
		{
			if ((i != index || j != 0) && (i != index + 1 || j != 1))
				close(e->fd[i][j]);
			j++;
		}
		i++;
	}
}

void	close_last(t_exec *e)
{
	int	i;
	int	j;

	if (!e->pipes)
		return ;
	i = 0;
	while (i < e->pipes)
	{
		j = 0;
		while (j < 2)
		{
			if (i != 1 || j != 0)
				close(e->fd[i][j]);
			j++;
		}
		i++;
	}
}

void	close_fd(t_exec *e, int index)
{
	if (!e->pipes)
		return ;
	if (index == 0)
		close(e->fd[0][1]);
	else if (index == e->pipes)
		close(e->fd[e->pipes - 1][0]);
	else
	{
		close(e->fd[index - 1][0]);
		close(e->fd[index][1]);
	}
}

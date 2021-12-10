/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:35:42 by vintran           #+#    #+#             */
/*   Updated: 2021/12/10 15:54:56 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	open_infiles(t_mini *m, t_exec *e)
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
		if (e->infile < -1)
			return (-1);
		if (g_vars.g_error == 130)
			return (-130);
		tmp = tmp->next;
	}
	return (0);
}

int	open_files(t_mini *m, t_exec *e)
{
	t_list	*tmp;
	int		ret;

	ret = open_infiles(m, e);
	if (ret < 0)
		return (ret);
	tmp = m->out[e->i];
	while (tmp)
	{
		if (tmp->type == 1)
			e->outfile
				= open((char *)tmp->data, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp->type == 2)
			e->outfile
				= open((char *)tmp->data, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (e->outfile == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

void	get_strs(t_exec *e, t_mini *m, int lstlen)
{
	int		i;
	t_list	*tmp;

	i = 0;
	e->strs[lstlen] = NULL;
	tmp = m->s[e->i];
	e->strs[0] = e->cmdpath;
	if (e->strs[0] && ft_strcmp((char *)tmp->data, "..")) {
		i = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		e->strs[i++] = (char *)tmp->data;
		tmp = tmp->next;
	}
}

int	init_forking(t_mini *m, t_exec *e)
{
	int		lstlen;
	int		ret;

	ret = open_files(m, e);
	if (ret < 0)
		return (ret);
	lstlen = lst_len(&m->s[e->i]);
	if (lstlen == 0)
		return (-2);
	if (!e->builtin)
	{
		e->cmdpath = get_cmdpath((char *)m->s[e->i]->data, e->path);
		e->strs = malloc(sizeof(char *) * (lstlen + 1));
		if (!e->strs)
		{
			malloc_error();
			return (-2);
		}
		get_strs(e, m, lstlen);
	}
	return (0);
}

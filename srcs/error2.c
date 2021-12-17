/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:49:42 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 12:50:44 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	execve_error(t_exec *e, t_mini *m)
{
	int	fd;
	int	ret;

	ret = 127;
	if (is_slash(e->strs[0]) && ft_strcmp(e->strs[0], ""))
	{
		fd = open(e->strs[0], O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(e->strs[0], STDERR_FILENO);
			ft_putstr_fd(" is a directory\n", STDERR_FILENO);
			ret = 126;
		}
		else
			perror("minishell");
	}
	else
		cmd_not_found(e->strs[0]);
	lst_clear(&g_vars.env, &free);
	free_mini_struct(m);
	free_exec_struct(e, 1);
	exit(ret);
}

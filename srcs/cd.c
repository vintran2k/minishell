/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:54:46 by vintran           #+#    #+#             */
/*   Updated: 2021/12/09 14:19:30 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	cd(t_list *lst)
{
	lst = lst->next;
	if (lst == NULL)
	{
		if (chdir("/~/") == -1)
		{
			perror("minishell");
			g_vars.g_error = 1;
			return ;
		}
	}
	else
	{
		if (chdir((char *)lst->data) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd((char *)lst->data, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			g_vars.g_error = 1;
			return ;
		}
	}
	g_vars.g_error = 0;
}

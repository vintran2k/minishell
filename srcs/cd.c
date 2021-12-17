/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:54:46 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 15:46:12 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	cd(t_dlist *lst)
{
	lst = lst->next;
	if (lst == NULL)
	{
		if (chdir("/~") == -1)
		{
			perror("minishell");
			return (1);
		}
	}
	else
	{
		if (chdir((char *)lst->data) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd((char *)lst->data, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:54:46 by vintran           #+#    #+#             */
/*   Updated: 2021/12/21 14:39:22 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*find_home(void)
{
	t_dlist	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (ft_strncmp(tmp->data, "HOME=", 5) == 0)
			return (&((char *)tmp->data)[5]);
		tmp = tmp->next;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (NULL);
}

int	cd_home(void)
{
	char	*home;

	home = find_home();
	if (home == NULL)
		return (1);
	if (!*home)
		return (0);
	if (chdir(find_home()) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(home, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	cd(t_dlist *lst)
{
	lst = lst->next;
	if (lst == NULL)
		return (cd_home());
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

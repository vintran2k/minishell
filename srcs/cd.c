/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:54:46 by vintran           #+#    #+#             */
/*   Updated: 2021/12/22 17:58:39 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_pwd_env(void)
{
	t_dlist	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, "PWD=", 4))
			return (strchr(tmp->data, '=') + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

void	replace_wd(t_dlist *lst, char *home, int status)
{
	char	*path;
	char	*new;

	if (status == 7)
		path = get_pwd_env();
	else
	{
		path = home;
		if (!path)
			path = getcwd(NULL, 0);
	}
	new = malloc(status + ft_strlen(path) + 1);
	if (!new)
		return ;
	new[0] = '\0';
	ft_strncat(new, lst->data, status);
	ft_strcat(new, path);
	free(lst->data);
	lst->data = new;
}

void	maj_wd(char *home)
{
	t_dlist	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, "OLDPWD=", 7))
			replace_wd(tmp, home, 7);
		tmp = tmp->next;
	}
	tmp = g_vars.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, "PWD=", 4))
			replace_wd(tmp, home, 4);
		tmp = tmp->next;
	}
}

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
	maj_wd(home);
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
		maj_wd(NULL);
	}
	return (0);
}

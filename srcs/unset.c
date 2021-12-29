/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 02:56:31 by vintran           #+#    #+#             */
/*   Updated: 2021/12/29 15:38:08 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_valid_unset(char *var)
{
	int	i;

	i = 0;
	if (isalpha(var[0]) == 0 && var[i] != '_')
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(var, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_export(char *var)
{
	t_dlist	*temp;

	temp = g_vars.export;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			if (temp == g_vars.export)
				g_vars.export = g_vars.export->next;
			lst_delone(temp);
			return (0);
		}
		temp = temp->next;
	}
	return (0);
}

void	unset_env(char *var)
{
	t_dlist	*temp;

	temp = g_vars.env;
	if (!ft_strcmp(var, "_"))
		return ;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			if (temp == g_vars.env)
				g_vars.env = g_vars.env->next;
			lst_delone(temp);
			return ;
		}
		temp = temp->next;
	}
}

int	unset(t_dlist *lst)
{
	int	ret;

	ret = 0;
	lst = lst->next;
	while (lst)
	{
		if (is_valid_unset(lst->data) == 1)
			ret = 1;
		if (ret != 1)
		{
			unset_env(lst->data);
			unset_export(lst->data);
		}
		lst = lst->next;
	}
	return (ret);
}

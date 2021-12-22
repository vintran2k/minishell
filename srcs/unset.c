/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 02:56:31 by vintran           #+#    #+#             */
/*   Updated: 2021/12/20 13:25:33 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_valid_unset(char *var)
{
	int	i;
	
	i = 0;
	while (var[i - 1])
	{
		if (ft_isalpha(var[i]) == 0 && var[i] != '_')
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
	t_dlist *temp;
	
	temp = g_vars.export;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			lst_delone(temp);
			return (0);	
		}
		temp = temp->next;
	}
	return (0);
}

int	unset_env(char *var)
{
	t_dlist *temp;
	
	temp = g_vars.env;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			lst_delone(temp);
			return (0);	
		}
		temp = temp->next;
	}
	return (0);
}

int	unset(char **var)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (var[i])
	{
		if (is_valid_unset(var[i]) == 1)
			ret = i;
		if (ret != i)
		{
			unset_env(var[i]);
			unset_export(var[i]);
		}
		i++;
	}
	return (ret > 0);
}

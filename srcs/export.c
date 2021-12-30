/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:51:29 by vintran           #+#    #+#             */
/*   Updated: 2021/12/30 14:48:01 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	var_add_export(char *var, char *p)
{
	t_dlist	*temp;
	char	*new_str;

	temp = g_vars.export;
	new_str = NULL;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			new_str = malloc(ft_strlen((char *)temp->data) + ft_strlen(p) + 1);
			new_str[0] = '\0';
			ft_strcat(new_str, (char *)temp->data);
			ft_strcat(new_str, p + 1);
			free(temp->data);
			temp->data = new_str;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	var_add_env(char *var, char *p)
{
	t_dlist	*temp;
	char	*new_str;

	temp = g_vars.env;
	new_str = NULL;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			new_str = malloc(sizeof(char) * ft_strlen((char *)temp->data)
					+ ft_strlen(p) + 1);
			new_str[0] = '\0';
			ft_strcat(new_str, (char *)temp->data);
			ft_strcat(new_str, p + 1);
			free(temp->data);
			temp->data = new_str;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void	find_var_env(char *full_var, char *var)
{
	t_dlist	*temp;
	int		ret;

	ret = 0;
	temp = g_vars.env;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			free(temp->data);
			temp->data = ft_strdup(full_var);
			ret = 1;
		}
		temp = temp->next;
	}
	if (ret == 0)
		push_back(&g_vars.env, ft_strdup(full_var));
}

void	find_var_export(char *full_var, char *var)
{
	t_dlist	*temp;
	int		ret;

	ret = 0;
	temp = g_vars.export;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			free(temp->data);
			temp->data = ft_strdup(full_var);
			ret = 1;
		}
		temp = temp->next;
	}
	if (ret == 0)
		push_back(&g_vars.export, ft_strdup(full_var));
}

int	export(t_dlist *lst)
{
	int		ret;
	char	*var;
	char	*p;

	ret = 0;
	lst = lst->next;
	if (lst == NULL)
		print_export();
	while (lst)
	{
		var = get_var(lst->data, &ret);
		if (ret == 1)
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(var, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
		p = ft_strchr(lst->data, '=');
		export_choice(lst->data, var, p);
		free(var);
		lst = lst->next;
	}
	return (ret > 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:51:29 by vintran           #+#    #+#             */
/*   Updated: 2021/12/22 12:16:25 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_var(char *s)
{
	int	i;
	char	*var;
	i = 0;
	if (!isalpha(s[0]))
		return (NULL);
	while (s[i] && s[i] != '=' && s[i] != '+')
	{
		if (i != 0 && !isalnum(s[i]))
			return (NULL);
		i++;
	}
	var = ft_strndup(s, i);
	return (var);
}

int	var_add_export(char *var, char *p)
{
	t_dlist *temp;
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
	t_dlist *temp;
	char	*new_str;
	
	temp = g_vars.env;
	new_str = NULL;
	while (temp)
	{
		if (ft_strncmp(var, (char *)temp->data, ft_strlen(var)) == 0)
		{
			new_str = malloc(sizeof(char) * ft_strlen((char *)temp->data) + ft_strlen(p) + 1);
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
	t_dlist *temp;
	int	ret;

	ret = 0;
	temp = g_vars.env;
	while (temp)
	{
		if (ft_strcmp(var, (char *)temp->data) == 0)
		{
			free(temp->data);
			temp->data = ft_strdup(full_var);
			ret = 1;
		}
		temp = temp->next;
	}
	if (ret == 0)
		push_back(&g_vars.env, ft_strdup(full_var));	
	temp = g_vars.export;
	while (temp)
	{
		if (ft_strcmp(var, (char *)temp->data) == 0)
		{
			free(temp->data);
			temp->data = ft_strdup(full_var);
			ret = 2;
		}
		temp = temp->next;	
	}
	if (ret != 2)
		push_back(&g_vars.export, ft_strdup(full_var));
}

int	export(char **tab_var)
{
	int	i;
	int	ret;
	char	*var;
	char	*p;

	i = 1;
	ret = 0;
	while (tab_var[i])
	{
		var = get_var(tab_var[i]);
		if (!var)
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(var, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			
		}
		p = ft_strchr(tab_var[i], '=');
		if (!p)
			push_back(&g_vars.export, tab_var[i]);
		else if (p[-1] == '+')
		{
			if (var_add_export(var, p) == 1)
				push_back(&g_vars.export, tab_var[i]);
			if (var_add_env(var, p) == 1)
				push_back(&g_vars.env, tab_var[i]);
		}
		else
			find_var_env(tab_var[i], var);
		i++;
	}
	printf("\n\n------------------env------------------\n");
	print_env(g_vars.env);
	printf("\n\n------------------export------------------\n");
	print_export(g_vars.export);
	return (ret > 0);
}
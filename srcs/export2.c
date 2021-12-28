/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:39:12 by vintran           #+#    #+#             */
/*   Updated: 2021/12/28 12:39:49 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_var(char *s, int *ret)
{
	int		i;
	char	*var;

	i = 0;
	if (!isalpha(s[0]) && s[0] != '_')
		*ret = 1;
	while (s[i] == '_')
		s++;
	while (s[i] && s[i] != '=')
	{
		if (i != 0 && !isalnum(s[i]))
			*ret = 1;
		i++;
	}
	var = ft_strndup(s, i);
	if (var[i - 1] == '+' && s[i] == '=')
	{
		var[i - 1] = '\0';
		*ret = 0;
	}
	return (var);
}

void	export_choice(char *full_var, char *var, char *p)
{
	if (!p)
		push_back(&g_vars.export, full_var);
	else if (p[-1] == '+')
	{
		if (var_add_export(var, p) == 1)
			push_back(&g_vars.export, full_var);
		if (var_add_env(var, p) == 1)
			push_back(&g_vars.env, full_var);
	}
	else
	{
		find_var_env(full_var, var);
		find_var_export(full_var, var);
	}
}

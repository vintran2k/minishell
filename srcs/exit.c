/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:38:53 by vintran           #+#    #+#             */
/*   Updated: 2021/12/28 13:47:58 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	loop_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	loop_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit_error(t_dlist *lst)
{
	if (lst->next && lst->next != NULL && lst->next->next != NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (lst->next && loop_alpha((char *)lst->next->data) != 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: numeric argument required\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_exit(t_dlist *lst, t_mini *m, t_exec *e)
{
	int	ret;

	if (ft_exit_error(lst) == 1)
		return (1);
	else if (lst->next && loop_digit((char *)lst->next->data) != 0
		&& lst->next->next == NULL)
	{
		ret = ft_atoi((char *)lst->next->data);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_mini_struct(m);
		free_exec_struct(e, 1);
		lst_clear(&g_vars.env, &free);
		lst_clear(&g_vars.export, &free);
		exit(ret % 256);
	}
	else if (lst->next == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_mini_struct(m);
		free_exec_struct(e, 1);
		lst_clear(&g_vars.env, &free);
		lst_clear(&g_vars.export, &free);
		exit(0);
	}
	return (0);
}

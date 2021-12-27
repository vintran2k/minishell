/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:38:53 by vintran           #+#    #+#             */
/*   Updated: 2021/12/27 18:22:00 by vintran          ###   ########.fr       */
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

int	ft_exit(t_dlist *lst)
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
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(lst->data, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (1);
	}
	else if (lst->next && loop_digit((char *)lst->next->data) != 0 && lst->next->next == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit (ft_atoi((char *)lst->next->data));
		return (ft_atoi((char *)lst->next->data));
	}
	else if (lst->next == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit (0);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:56:14 by vintran           #+#    #+#             */
/*   Updated: 2021/12/10 12:43:22 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	echo(t_list *lst)
{
	int	i;
	int	opt;

	i = 1;
	opt = 0;
	lst = lst->next;
	if (lst && strcmp((char *)lst->data, "-n") == 0)
	{
		lst = lst->next;
		opt = 1;
		i++;
	}
	while (lst)
	{
		ft_putstr_fd((char *)lst->data, STDOUT_FILENO);
		if (lst->next != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		lst = lst->next;
		i++;
	}
	if (i == 1 || opt == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_vars.g_error = 0;
}

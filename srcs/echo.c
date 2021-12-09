/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:56:14 by vintran           #+#    #+#             */
/*   Updated: 2021/12/09 14:12:48 by vintran          ###   ########.fr       */
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
		printf("%s", (char *)lst->data);
		if (lst->next != NULL)
			printf(" ");
		lst = lst->next;
		i++;
	}
	if (i == 1 || opt == 0)
		printf("\n");
	g_vars.g_error = 0;
}

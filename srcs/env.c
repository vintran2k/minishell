/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:32:56 by thpham-v          #+#    #+#             */
/*   Updated: 2021/12/22 12:29:51 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_quotation(char *str)
{
	int i;
	int	equal;

	i = 0;
	equal = 0;
	while (str[i])
	{
		write(1, &str[i++], 1);
		if (str[i - 1] == '=' && equal == 0)
		{
			write(1, "\"", 1);
			equal = 1;
		}
	}
	if (equal != 0)
		write(1, "\"", 1);
}

void	sort_lst_env(t_dlist **lst_export)
{	
	char	*temp;
	t_dlist	*lst_temp1;
	t_dlist	*lst_temp2;

	lst_temp1 = *lst_export;
	while (lst_temp1)
	{
		lst_temp2 = lst_temp1->next;
		while (lst_temp2)
		{
			if (ft_strcmp(lst_temp1->data, lst_temp2->data) > 0)
			{
				temp = lst_temp1->data;
				lst_temp1->data = lst_temp2->data;
				lst_temp2->data = temp;
			}
			lst_temp2 = lst_temp2->next;
		}
		lst_temp1 = lst_temp1->next;
	}
}

int		print_env(void)
{
	t_dlist	*temp;

	temp = g_vars.env;
	while (temp)
	{
		ft_putstr_fd(temp->data, 1);
		write(1, "\n", 1);
		temp = temp->next;
	}
	return (0);
}

void	print_export(void)
{
	t_dlist	*temp;

	sort_lst_env(&g_vars.export);
	temp = g_vars.export;
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		print_quotation(temp->data);
		write(1, "\n", 1);
		temp = temp->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:56:14 by vintran           #+#    #+#             */
/*   Updated: 2021/12/13 02:30:58 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putstr_fd("2147483648", fd);
			return ;
		}
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

int	echo(t_list *lst)
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
		if (strcmp((char *)lst->data, "$?") == 0)
			ft_putnbr_fd(g_vars.error, STDOUT_FILENO);
		else
			ft_putstr_fd((char *)lst->data, STDOUT_FILENO);
		if (lst->next != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		lst = lst->next;
		i++;
	}
	if (i == 1 || opt == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

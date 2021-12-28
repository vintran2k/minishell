/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:06:48 by vintran           #+#    #+#             */
/*   Updated: 2021/12/27 19:39:10 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	sigint_here_doc(int signal)
{
	(void)signal;
	g_vars.error = 130;
	free(g_vars.eof);
	lst_clear(&g_vars.env, &free);
	lst_clear(&g_vars.export, &free);
	ft_putchar_fd('\n', STDIN_FILENO);
	exit(130);
}

void	main_signal(int signal)
{
	kill(g_vars.pid, signal);
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		g_vars.error = 131;
	}
	else if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_vars.error = 130;
	}
}

void	ft_signal(int signal)
{
	if ((signal == SIGINT || signal == SIGQUIT) && g_vars.pid != 0)
		main_signal(signal);
	else
	{
		if (signal == SIGINT)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			g_vars.error = 1;
			get_prompt(1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (signal == SIGQUIT)
			ft_putstr_fd("Quit\n", STDOUT_FILENO);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:06:48 by vintran           #+#    #+#             */
/*   Updated: 2021/12/27 18:23:28 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	sigint_main(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	g_vars.error = 1;
	get_prompt(1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_here_doc(int signal)
{
	(void)signal;
	rl_clear_history();
	g_vars.error = 130;
	free(g_vars.eof);
	lst_clear(&g_vars.env, &free);
	lst_clear(&g_vars.export, &free);
	write(1, "\n", 1);
	exit(130);
}

void	sigint_fork(int signal)
{
	(void)signal;
	g_vars.error = 130;
	write(1, "\n", 1);
}

void	sigquit_fork(int signal)
{
	(void)signal;
	g_vars.error = 131;
	write(1, "Quit (core dumped)\n", 19);
}

void	main_signal(int signal)
{
	kill(g_vars.pid, signal);
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		g_vars.error = 131;
	}
	else if (signal == SIGINT)
	{
		ft_putstr_fd("\n1", STDOUT_FILENO);
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
			ft_putstr_fd("\n3", STDOUT_FILENO);
			g_vars.error = 1;
			get_prompt(1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (signal == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
}

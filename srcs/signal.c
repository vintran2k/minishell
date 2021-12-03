/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:06:48 by vintran           #+#    #+#             */
/*   Updated: 2021/12/03 18:09:38 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	sigint_main(int signal)
{
	(void)signal;
	write(1, "\n$ ", 3);
	//write(1, "\n", 1);
	g_vars.g_error = 1;
}

void	sigint_here_doc(int signal)
{
	(void)signal;
	rl_clear_history();
	g_vars.g_error = 130;
	free(g_vars.g_eof);
	exit(130);
}

void	sigint_fork(int signal)
{
	(void)signal;
	g_vars.g_error = 130;
	write(1, "\n", 1);
}

void	sigquit_fork(int signal)
{
	(void)signal;
	g_vars.g_error = 131;
	write(1, "Quit\n", 5);
}

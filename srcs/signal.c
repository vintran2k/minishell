/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:06:48 by vintran           #+#    #+#             */
/*   Updated: 2021/12/07 12:49:50 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	sigint_main(int signal)
{
	(void)signal;
	char	*prompt;

	rl_replace_line("", 0);
	rl_redisplay();
	g_vars.g_error = 1;
	prompt = get_prompt();
	printf("\n%s", prompt);
	free(prompt);
}

void	sigint_here_doc(int signal)
{
	(void)signal;
	rl_clear_history();
	g_vars.g_error = 130;
	free(g_vars.g_eof);
	lst_clear(&g_vars.env, &free);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:51:32 by vintran           #+#    #+#             */
/*   Updated: 2021/12/21 14:49:56 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_prompt(int arrow)
{
	char	*prompt;
	char	*cwd;
	int		i;

	if (g_vars.error == 0)
		printf("\033[1;32m➜ \033[0m");
	else
		printf("\033[1;31m➜ \033[0m");
	if (arrow == 1)
		return (NULL);
	cwd = getcwd(NULL, 0);
	i = ft_strlen(cwd) - 1;
	while (i > 0)
	{
		if (cwd[i - 1] == '/')
			break ;
		i--;
	}
	if (i == 1)
		i--;
	prompt = malloc(ft_strlen(&cwd[i]) + 16);	//
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strcat(prompt, "\033[1;34m");
	ft_strcat(prompt, &cwd[i]);
	ft_strcat(prompt, " \033[0m");
	free(cwd);
	return (prompt);
}

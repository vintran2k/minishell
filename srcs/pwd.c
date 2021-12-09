/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:57:40 by vintran           #+#    #+#             */
/*   Updated: 2021/12/09 14:12:01 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

void	pwd(void)
{
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = getcwd(buf, 0);
	if (pwd == NULL)
	{
		g_vars.g_error = 1;
		return ;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	g_vars.g_error = 0;
}

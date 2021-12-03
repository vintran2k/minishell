/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:21:18 by vintran           #+#    #+#             */
/*   Updated: 2021/12/03 17:21:49 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_cmdpath(char *cmd, char **path)
{
	char	*cmdpath;
	int		i;
	int		cmdlen;
	int		pathlen;

	cmdlen = ft_strlen(cmd);
	i = -1;
	while (path[++i])
	{
		pathlen = ft_strlen(path[i]);
		cmdpath = malloc(pathlen + cmdlen + 2);
		if (!cmdpath)
			return (NULL);
		ft_strcpy(cmdpath, path[i]);
		cmdpath[pathlen] = '/';
		cmdpath[pathlen + 1] = '\0';
		ft_strcat(cmdpath, cmd);
		if (!access(cmdpath, F_OK))
			return (cmdpath);
		free(cmdpath);
	}
	return (NULL);
}

char	**get_env_path(char **env)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			res = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (res);
}

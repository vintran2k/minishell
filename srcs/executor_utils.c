/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:21:18 by vintran           #+#    #+#             */
/*   Updated: 2021/12/29 15:40:52 by vintran          ###   ########.fr       */
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
	while (path && path[++i])
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

char	**lst_to_char(t_dlist *lst)
{
	t_dlist	*tmp;
	int		len;
	char	**res;
	int		i;

	if (!lst)
		return (NULL);
	len = lst_len(&lst);
	res = malloc(sizeof(char *) * (len + 1));
	res[len] = NULL;
	tmp = lst;
	i = 0;
	while (tmp)
	{
		res[i++] = ft_strdup(tmp->data);
		tmp = tmp->next;
	}
	return (res);
}

int	ft_shlvl(char *cmd)
{
	char	*slash;

	slash = ft_strchr(cmd, '/');
	while (slash)
	{
		cmd = slash + 1;
		slash = ft_strchr(slash + 1, '/');
	}
	if (!ft_strcmp(cmd, "minishell"))
		return (1);
	return (0);
}

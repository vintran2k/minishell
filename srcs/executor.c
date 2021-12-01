/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:39:07 by vintran           #+#    #+#             */
/*   Updated: 2021/11/26 18:12:17 by vintran          ###   ########.fr       */
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

#define TMP_FILE	"/tmp/minishell_tmp"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
	}
}

int	create_tmp_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY |O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		ft_putstr_fd("minishell: open error in redirect\n", STDERR_FILENO);
	return (fd);
}

void	exit_here_doc(int signal)
{
	(void)signal;
	//fprintf(stderr, "passage\n");
	//fprintf(stderr, "passage avant error.exit\n");
	//error.exit = 130;
	//fprintf(stderr, "passage avant exit(130)\n");
	rl_clear_history();
	g_vars.g_error = 130;
	free(g_vars.g_eof);
	exit(130);
}

int	here_doc(t_exec *e, t_mini *m)
{
	char	*line;
	int		fd;
	pid_t	pid;
	int		status;

	fd = create_tmp_file();
	if (fd == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		free_mini_struct(m);
		free_exec_struct(e, 1);
		signal(SIGINT, exit_here_doc);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted '", STDERR_FILENO);
				ft_putstr_fd(g_vars.g_eof, 2);
				ft_putstr_fd("')\n", 2);
				close(fd);
				rl_clear_history();
				free(g_vars.g_eof);
				exit(0);
			}
			if (ft_strcmp(line, g_vars.g_eof))
				ft_putendl_fd(line, fd);
			else
			{
				free(line);
				close(fd);
				break ;
			}
			free(line);
		}
		rl_clear_history();
		free(g_vars.g_eof);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
		close(fd);
		g_vars.g_error = 130;
	}
	fd = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
	return (fd);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	slen;
	size_t	i;

	slen = ft_strlen((char *)s);
	if (!(dst = malloc(sizeof(char) * (slen + 1))))
		return (NULL);
	i = 0;
	while (i < slen)
	{
		dst[i] = s[i];
		i++;
	}
	dst[slen] = '\0';
	return (dst);
}

int	open_files(t_mini *m, t_exec *e)
{
	t_list	*tmp;

	tmp = m->in[e->i];
	while (tmp)
	{
		if (tmp->type == 1)
			e->infile = open((char *)tmp->data, O_RDONLY);
		if (e->infile == -1)
			return (-1);
		if (tmp->type == 2)
		{
			g_vars.g_eof = ft_strdup((char *)tmp->data);
			e->infile = here_doc(e, m);
			free(g_vars.g_eof);
		}
		if (e->infile == -1)
			return (-1);
		if (g_vars.g_error == 130)
			return (-130);
		tmp = tmp->next;
	}
	tmp = m->out[e->i];
	while (tmp)
	{
		if (tmp->type == 1)
			e->outfile = open((char *)tmp->data, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp->type == 2)
			e->outfile = open((char *)tmp->data, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (e->outfile == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

void	execve_error(t_exec *e)
{
	ft_putstr_fd("execve error a gerer\n", STDERR_FILENO);
	
	exit (1);
}

int	first_fork(char **env, t_exec *e)
{
	if (e->infile)
		dup2(e->infile, STDIN_FILENO);
	if (e->outfile)
		dup2(e->outfile, STDOUT_FILENO);
	else if (e->pipes)
		dup2(e->fd[0][1], STDOUT_FILENO);
	close_first(e);
	if (execve(e->strs[0], e->strs, env) == -1)
		execve_error(e);
	return (0);
}

int	mid_fork(char **env, t_exec *e, int i)
{
	if (e->infile)
		dup2(e->infile, STDIN_FILENO);
	else
		dup2(e->fd[i - 1][0], STDIN_FILENO);
	if (e->outfile)
		dup2(e->outfile, STDOUT_FILENO);
	else
		dup2(e->fd[i][1], STDOUT_FILENO);
	close_mid(e, i);
	if (execve(e->strs[0], e->strs, env) == -1)
		execve_error(e);
	return (0);
}

int	last_fork(char **env, t_exec *e)
{
	if (e->infile)
		dup2(e->infile, STDIN_FILENO);
	else
		dup2(e->fd[e->pipes - 1][0], STDIN_FILENO);
	if (e->outfile)
		dup2(e->outfile, STDOUT_FILENO);
	close_last(e);
	if (execve(e->strs[0], e->strs, env) == -1)
		execve_error(e);
	return (0);
}

int	forking(char **env, t_mini *m, t_exec *e)
{
	e->ret = init_forking(m, e);
	if (e->ret == -1)
			perror("minishell");
	if (e->ret == 0)
	{
		e->pid[e->i] = fork();
		if (e->pid[e->i] == 0)
		{
			rl_clear_history();
			if (e->i == 0)
				e->ret = first_fork(env, e);
			else if (e->i == e->pipes)
				e->ret = last_fork(env, e);
			else
				e->ret = mid_fork(env, e, e->i);
			
		}
	}
	close_fd(e, e->i);
	free_exec_struct(e, 0);
	if (e->infile)
	{
		close(e->infile);
		e->infile = 0;
	}
	if (e->outfile)
	{
		close(e->outfile);
		e->outfile = 0;
	}
	return (e->ret);
}

int	executor(t_mini *m, char **env)
{
	t_exec	e;

	if (init_exec(&e, m, env) == -1)
	{
		free_exec_struct(&e, 1);
		return (-1);
	}
	e.i = 0;
	while (e.i <= m->n_pipes)
	{
		forking(env, m, &e);
		if (e.ret == 0)
			e.fork[e.i] = 1;
		if (e.ret == -130)
		{
			write(1, "\n", 1);
			break ;
		}
		e.i++;
	}
	e.i = 0;
	while (e.i <= e.pipes)
	{
		if (e.fork[e.i])
		{
			waitpid(e.pid[e.i], &e.status, 0);
			if (WIFEXITED(e.status))
				e.exit = WEXITSTATUS(e.status);
		}
		e.i++;
	}
	free_exec_struct(&e, 1);
	return (0);
}

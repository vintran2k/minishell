/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:16:26 by vintran           #+#    #+#             */
/*   Updated: 2021/12/24 15:00:27 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#define TMP_FILE	"/tmp/minishell_tmp"

int	create_tmp_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		ft_putstr_fd("minishell: open error in redirect\n", STDERR_FILENO);
	return (fd);
}

void	read_here_doc_loops(int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			here_doc_warning();
			close(fd);
			free(g_vars.eof);
			exit(0);
		}
		if (ft_strcmp(line, g_vars.eof))
			ft_putendl_fd(line, fd);
		else
		{
			free(line);
			close(fd);
			break ;
		}
		free(line);
	}
}

int	here_doc(t_exec *e, t_mini *m)
{
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
		free_here_doc_process(m, e);
		signal(SIGINT, sigint_here_doc);
		read_here_doc_loops(fd);
		free(g_vars.eof);
		exit(0);
	}
	g_vars.error = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		g_vars.error = 130;
	fd = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
	return (fd);
}

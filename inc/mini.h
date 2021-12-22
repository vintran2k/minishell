#ifndef MINI_H
# define MINI_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_dlist
{
	int				type;
	void			*data;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}				t_dlist;

typedef struct	s_lexer
{
	int		i;
	int		j;
	int		q;
	int		dq;
	char	*sep;
	t_dlist	*lst;
}				t_lexer;

typedef struct	s_mini
{
	int		n_pipes;
	t_dlist	**s;
	t_dlist	**in;
	t_dlist	**out;
}				t_mini;

typedef struct	s_exec
{
	int		i;
	int		ret;
	int		pipes;
	int		status;
	int		exit;
	char	**path;
	int		**fd;
	char	*cmdpath;
	int		infile;
	int		outfile;
	char	**strs;
	pid_t	*pid;
	int		builtin;
}				t_exec;

typedef	struct	s_global
{
	int		error;
	char	*eof;
	t_dlist	*env;
	t_dlist	*export;
}				t_global;

t_global	g_vars;

/*
** LIST ----------------------------------------------------------------- **
*/

t_dlist		*create_elem(void *data);
void		push_back(t_dlist **lst, void *data);
int			lst_len(t_dlist **lst);
int			lst_delone(t_dlist *lst);
void		lst_clear(t_dlist **lst, void (*del)(void *));

/*
** PARSING -------------------------------------------------------------- **
*/

void		lexer(char *line, t_lexer *a);
char		*is_in_env(char *s);
int			get_newlen(char *s, char *env, int dq);
void		fill_new(char *dst, char *src, char *env, int beg);
int			var_len(char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			itoa_len(int n);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
char		*ft_strncat(char *dest, char *src, int n);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strndup(char *src, int n);
void		free_split(char **tab);
char		*get_prompt(int arrow);
int			is_quote_closed(t_lexer *a);
int			quote_maj(t_lexer *a, char c);
void		init_lexer(t_lexer *a);
t_dlist		**split_pipes(t_dlist *lst, int n_pipes);
void		parse_vars(t_lexer *a);
int			parser(t_dlist **lst, t_mini *m);
int			remove_quotes(t_mini *m);
int			get_redirections(t_mini *m);

/*
** BUILTINS ------------------------------------------------------------- **
*/

void		print_env(t_dlist *lst_env);
void		print_export(t_dlist *lst_export);
int			cd(t_dlist *lst);
int			echo(t_dlist *lst);
int			pwd(void);
int			export(char **tab_var);
int			unset(char **var);

/*
** EXECUTION ------------------------------------------------------------ **
*/

char		**get_env_path(char **env);
char		*get_cmdpath(char *cmd, char **path);
int			init_exec(t_exec *e, t_mini *m, char **env);
int			init_forking(t_mini *m, t_exec *e);
int			forking(char **env, t_mini *m, t_exec *e);
void		quit_forking(t_exec *e);
int			first_fork(char **env, t_exec *e, t_mini *m);
int			mid_fork(char **env, t_exec *e, t_mini *m, int i);
int			last_fork(char **env, t_exec *e, t_mini *m);
int			init_exec(t_exec *e, t_mini *m, char **env);
int			executor(t_mini *m, char **env);
int			exec_builtins(t_mini *m, t_exec *e);
int			here_doc(t_exec *e, t_mini *m);
void		close_first(t_exec *e);
void		close_mid(t_exec *e, int i);
void		close_last(t_exec *e);
void		close_fd(t_exec *e, int i);

/*
** SIGNALS -------------------------------------------------------------- **
*/

void		sigint_main(int signal);
void		sigint_here_doc(int signal);
void		sigint_fork(int signal);
void		sigquit_fork(int signal);

/*
** ERRORS --------------------------------------------------------------- **
*/

int			malloc_error(void);
void 		*malloc_error2(void);
int			redirections_error(t_dlist *lst);
void		here_doc_warning(void);
void		execve_error(t_exec *e, t_mini *m);

/*
** FREE ----------------------------------------------------------------- **
*/

void		free_mini_struct(t_mini *m);
void		free_exec_struct(t_exec *e, int finish);




#endif
#ifndef MINI_H
# define MINI_H

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

typedef struct	s_list
{
	int				type;
	void			*data;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef struct	s_lexer
{
	int		i;
	int		j;
	int		q;
	int		dq;
	char	*sep;
	t_list	*lst;
}				t_lexer;

typedef struct	s_mini
{
	int		n_pipes;
	t_list	**s;
	t_list	**in;
	t_list	**out;
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
	int		*fork;
}				t_exec;

typedef	struct	s_global
{
	int		g_error;
	char	*g_eof;
}				t_global;

t_global	g_vars;

t_list		*create_elem(void *data);
void		push_back(t_list **lst, void *data);
void		push_front(t_list **lst, void *data);
int			lst_len(t_list **lst);
int			lst_delone(t_list *lst);
void		lst_clear(t_list **lst, void (*del)(void *));
void		remove_top(t_list **lst);
t_list		*lexer(char *line, t_lexer *a);
void		ft_bzero(void *s, size_t n);
int			ft_strlen(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strndup(char *src, int n);
char		**ft_split(const char *s, char c);
void		free_split(char **tab);
int			malloc_error(void);
void 		*malloc_error2(void);
int			is_quote_closed(t_lexer *a);
int			quote_maj(t_lexer *a, char c);
void		init_lexer(t_lexer *a);
int			init_parser(t_mini *m, t_list *lst);
t_list		**split_pipes(t_list *lst, int n_pipes);
int			parser(t_list **lst, t_mini *m);
void		free_s(char ***s);
int			count_pipes(t_list *lst);
int			remove_quotes(t_mini *m);
int			redirections_error(t_list *lst);
int			get_redirections(t_mini *m);
void		free_mini_struct(t_mini *m);
char		**get_env_path(char **env);
char		*get_cmdpath(char *cmd, char **path);
int			open_files(t_mini *m, t_exec *e);
int			init_exec(t_exec *e, t_mini *m, char **env);
int			init_forking(t_mini *m, t_exec *e);
int			executor(t_mini *m, char **env);
void		free_exec_struct(t_exec *e, int finish);
void		close_first(t_exec *e);
void		close_mid(t_exec *e, int i);
void		close_last(t_exec *e);
void		close_fd(t_exec *e, int i);

#endif
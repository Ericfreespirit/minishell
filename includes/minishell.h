/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriling <eriling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:16:37 by eriling           #+#    #+#             */
/*   Updated: 2021/12/01 09:09:53 by eriling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include	"../libft/libft.h"
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<sys/types.h>
# include	<sys/wait.h>
# include	<sys/resource.h>
# include	<signal.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ERROR_ARG 1
# define ERROR_NUM 2
# define EQUAL 1
# define PLUS_EQUAL 2
# define MAX_PATH 4096
# define REDIRECTION 1
# define FILE 2
# define WORD 3
# define CTRL_C 1

typedef struct s_redir
{
	int				index;
	char			*file;
	int				hdoc_fd;
	struct s_redir	*next;
}				t_redir;

typedef struct s_hdoc
{
	int				fd;
	char			*end;
	struct s_hdoc	*next;
}		t_hdoc;

typedef struct s_ast
{
	char			**arg;
	t_redir			*redir;
	t_hdoc			*hdoc;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_data
{
	char		**env;
	char		*prompt;
	char		*arg;
	char		**lex_fi;
	char		**tmp;
	int			exit;
	int			lst_pid;
	int			ret_exit;
	int			in_hdoc;
	int			in_child;
	int			stop;
	int			fd;
	int			chd_status;
	int			quit;
	t_ast		*node;
	char		*str;
}				t_data;

int		cd(char **arg, char ***envp);
int		pwd(void);
int		parsing(char *line, t_data *data);
void	env(char **envp);
int		export(char *var_name, char *var_val, int oper, char ***envp);
void	export_display(char ***envp);
int		to_find_varname(char *envp, char *to_find);
int		unset(char *var_name, char ***envp);
void	echo(char **arg);
int		ft_findchar(const char c, char *tab);
int		count_word_c(char *line, char c, char stop, int i);
char	*get_varname_val(char *var_name, char **envp);
int		launch_export(char **arg, char ***envp);
int		launch_unset(char **arg, char ***envp);
void	ft_exit(t_ast *node);
void	free_datatofree(t_data *data);
void	free_envp(char **envp);
void	ft_split_export(char **name, char **val, int *operation, char *arg);
int		is_var_env(char *var_name, char ***envp);
void	sorting_envp(char **envp);
void	handler_sigint(int sig);
void	handler_sigquit(int sig);
void	ft_sigquit(int code);
int		quit_hdoc(t_redir *redir, char *str, int ret);
void	free_exit(int statut, int error);
t_data	*sg(void);

int		prompt(void);
int		ft_findchar(const char c, char *tab);
int		var(char **line, size_t *i, size_t *len, t_data *data);
char	*set_env_var(char **line, int i, int n, t_data *data);
int		check_quote(char *line, char c);
void	*ft_free(void *ptr);
int		free_ast(t_ast *node, int ret);
int		check_ast(t_ast *node);
void	ctrl_d(void);

// builtins
void	ft_execve(char **arg, char **envp);

// Free
void	free_program(void);

// Print
int		str_error(char *s, int ret, int status);
char	*str_error2(char *s, char *ret, int status);
void	printf_ast(t_ast *node);
void	err_msg(char *str, int fd, int status);

// Lexer
int		len_token(char *line);
int		len_arr(char **arg);
int		len_operator(char *line);
int		count_token(char *line);
int		get_lexical_field(char *line);
int		is_operator(char c);
int		is_redirection(char *s);
int		is_word(char *s);
int		is_quote(char c);
int		free_lexical_field(char **lex_fi, int ret);
int		is_quote(char c);
int		len_string_quoted(char *line, char quote);

// Hdoc
int		fork_hdoc(t_ast *node);
int		fork_rdl_hdoc(t_ast *node);

// Ast
int		get_tree(void);
char	*ft_replace_token(char *str);
void	store_node_data(t_ast *node, char *str, int type);
char	**realloc_node_arg(char **arg, char *str);
int		len_string(char *str);
int		len_string_quoted(char *line, char quote);
char	**free_arg(char **arg);
void	free_redir(t_redir *redir);
char	**free_arg(char **arg);
char	**free_arg_arr(char **arg, char **arr);
int		exec_ast(t_ast *node);
int		parsing_command(t_ast *node, char *cmd);
int		exec_redir(t_redir *redir);
void	printf_ast(t_ast *node);
int		write_hdoc(void);
int		exec_command(t_ast *node, char *cmd);
void	free_hdoc_node(t_hdoc *hdoc);
void	free_hdoc_ast(t_ast *node);
int		is_last_hdoc(t_redir *redir);
int		exec_hdoc(t_ast *node);
t_redir	*last_redir(t_redir *redir);
int		is_last_redir_hdoc(t_redir *redir);
void	handler_sigchild(int sig);
t_redir	*get_last_hdoc_ast(t_ast *node);
int		hdoc_backtracking(t_ast *node);
void	create_hdoc_list(t_ast *node, t_redir **hdoc_list);
void	free_hdoc_node(t_hdoc *hdoc);
int		add_fd_redir(t_ast *node, int fd);
int		is_last_hdoc(t_redir *redir);
char	*free_rdl_str(void);
void	handler_sigchild(int sig);
void	launch_minishell(void);
t_redir	*store_redir(char *str);
void	free_line_exit(char *line);
void	test(int sig);
void	fork_execve(t_ast *node);
void	ft_signal_ignored(void);
#endif

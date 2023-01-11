/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:19:35 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/07 13:01:39 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <signal.h>

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

# define NB_BUILTINS 7
# define BUFF_SIZE 300

typedef enum e_token_type
{
	logical_op_token,
	parenthesis_open_token,
	parenthesis_close_token,
	pipe_token,
	redirection_token,
	command_token
}	t_token_type;

typedef enum e_exit_status
{
	exit_success = 0,
	exit_failure = 1,
	exit_failed_builtin = 2,
	exit_cant_exec = 126,
	exit_cmd_not_found = 127,
	exit_invalid_arg = 128
}	t_exit_status;

typedef struct s_token
{
	t_token_type	type;
	char			*line;
	unsigned int	start;
	unsigned int	end;
}					t_token;

typedef struct s_astree
{
	t_token			*token;
	struct s_astree	*left;
	struct s_astree	*right;
}					t_astree;

typedef struct sigaction	t_sigaction;

typedef struct s_env
{
	char			**path;
	char			**envp;
	void			(*builtins[NB_BUILTINS])(struct s_env *, char **, int);
	t_exit_status	exit_status;
	t_astree		*tree;
}					t_env;

int				ft_get_builtin(char *cmd);
int				ft_init_env(t_env *env, char **envp);
int				ft_init_path(t_env *env, char **envp);
int				ft_get_op_precedence(t_dlist *op_stack, t_token *token);
int				ft_redir_is_operand(t_token *token,
					t_list *tokens, t_token *prev);

void			ft_cleanup(t_env *env);
void			ft_free_tab(char **tab);
void			ft_clean_astree(t_astree *tree);
void			ft_print_astree(t_astree *tree);

void			ft_minishell(t_env *env, char *prompt);

/* wildcard matching */
int				ft_match_wildcard(char *pattern, char *str);
char			**ft_parse_wildcards(char **argv);

/* commands error */
void			ft_perm_error(char *cmd);
void			ft_file_error(char *cmd);
void			ft_command_error(char *cmd);

/* execution commands execute*.c */
void			ft_execute(t_env *env, t_astree *tree,
					int stdin, int stdout);
void			ft_execute_pipe(t_env *env, t_astree *tree,
					int stdin, int stdout);
void			ft_execute_logic(t_env *env, t_astree *tree,
					int stdin, int stdout);
void			ft_execute_command(t_env *env, t_astree *tree,
					int stdin, int stdout);
void			ft_execute_redirection(t_env *env, t_astree *tree,
					int stdin, int stdout);

/* execution utilities functions execute_utils.c*/
void			ft_read_lines(char *line, char *lim, int fd);

/* execution split arguments utility split_args.c*/
char			**ft_split_args(char *cmd);

/* builtin commands */
void			ft_env(t_env *env, char **argv, int stdout);
void			ft_exit(t_env *env, char **argv, int stdout);
void			ft_echo(t_env *env, char **argv, int stdout);
void			ft_unset(t_env *env, char **argv, int stdout);
void			ft_export(t_env *env, char **argv, int stdout);
void			ft_cd(t_env *env, char **argv, int stdout);
void			ft_pwd(t_env *env, char **argv, int stdout);

char			*ft_get_astree_cmd(t_astree *tree);
char			*ft_get_cmd_path(char *cmd, char **path);

char			**ft_copy_tab(char **argv, size_t incr);
char			**ft_parse_env_variables(t_env *env, char **argv);

/* lexer creation lexer.c*/
t_list			*ft_lexer(char *line);

/*lexer utils lexer_utils.c*/
int				ft_check_miss_item(char *line);
t_token_type	ft_check_token_type(char *line, int start);
unsigned int	ft_get_token_end(char *line, t_token *token);

t_token			*ft_lst_next_token(t_list **tokens);

int				ft_is_open_parenthesis(t_dlist **node_stack);

t_astree		*ft_parser(t_list *tokens);
t_astree		*ft_create_astnode(t_token *token);
t_astree		*ft_dlist_to_astree(t_dlist *dlist);

/*signal management */
void			ft_sig_handler(int sig, siginfo_t *siginfo, void *context);

#endif

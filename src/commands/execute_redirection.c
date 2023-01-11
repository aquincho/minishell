/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:39:27 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 12:40:17 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_stdin_redirection(t_env *env, t_astree *tree, int stdout)
{
	int		fd;
	char	*tmp;
	char	*file;

	++tree->token->start;
	tmp = ft_get_astree_cmd(tree);
	file = ft_strtrim(tmp, " ");
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		if (errno == EACCES)
			ft_perm_error(file);
		else
			ft_file_error(file);
		free(tmp);
		free(file);
		env->exit_status = exit_failure;
		return ;
	}
	free(tmp);
	free(file);
	ft_execute(env, tree->left, fd, stdout);
}

static void	ft_stdout_redirection(t_env *env, t_astree *tree, int stdin)
{
	int		fd;
	char	*tmp;
	char	*file;

	++tree->token->start;
	tmp = ft_get_astree_cmd(tree);
	file = ft_strtrim(tmp, " ");
	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		ft_perm_error(file);
		free(tmp);
		free(file);
		env->exit_status = exit_failure;
		return ;
	}
	free(tmp);
	free(file);
	ft_execute(env, tree->left, stdin, fd);
}

static void	ft_stdout_append(t_env *env, t_astree *tree, int stdin)
{
	int		fd;
	char	*tmp;
	char	*file;

	tree->token->start += 2;
	tmp = ft_get_astree_cmd(tree);
	file = ft_strtrim(tmp, " ");
	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
	{
		ft_perm_error(file);
		free(tmp);
		free(file);
		env->exit_status = exit_failure;
		return ;
	}
	free(tmp);
	free(file);
	ft_execute(env, tree->left, stdin, fd);
}

static void	ft_stdin_heredoc(t_env *env, t_astree *tree, int stdout)
{
	int		fd;
	char	*tmp;
	char	*lim;
	char	*line;

	tree->token->start += 2;
	tmp = ft_get_astree_cmd(tree);
	lim = ft_strtrim(tmp, " ");
	fd = open("/tmp/heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0)
	{
		free (tmp);
		free (lim);
		env->exit_status = EXIT_FAILURE;
		return ;
	}
	line = NULL;
	ft_read_lines(line, lim, fd);
	free (tmp);
	free (lim);
	close (fd);
	fd = open("/tmp/heredoc_tmp", O_RDONLY);
	ft_execute(env, tree->left, fd, stdout);
}

void	ft_execute_redirection(t_env *env, t_astree *tree, int stdin,
			int stdout)
{
	if (tree->token->line[tree->token->start] == '<'
		&& tree->token->line[tree->token->start + 1] == '<')
		ft_stdin_heredoc(env, tree, stdout);
	else if (tree->token->line[tree->token->start] == '<')
		ft_stdin_redirection(env, tree, stdout);
	else if (ft_strncmp(">>", &tree->token->line[tree->token->start], 2))
		ft_stdout_redirection(env, tree, stdin);
	else
		ft_stdout_append(env, tree, stdin);
}

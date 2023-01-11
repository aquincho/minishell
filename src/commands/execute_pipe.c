/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:22:25 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/02 12:14:30 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute_left(t_env *env, t_astree *tree, int stdin, int fd[2])
{
	close(fd[0]);
	ft_execute(env, tree->left, stdin, fd[1]);
	close(fd[1]);
	exit(env->exit_status);
}

static void	ft_execute_right(t_env *env, t_astree *tree, int fd[2], int stdout)
{
	ft_execute(env, tree->right, fd[0], stdout);
	close(fd[0]);
	exit(env->exit_status);
}

void	ft_execute_pipe(t_env *env, t_astree *tree, int stdin, int stdout)
{
	pid_t	pipe1;
	pid_t	pipe2;
	int		fd[2];
	int		wstatus;

	pipe(fd);
	pipe1 = fork();
	if (pipe1 == 0)
		ft_execute_left(env, tree, stdin, fd);
	close(fd[1]);
	pipe2 = fork();
	if (pipe2 == 0)
		ft_execute_right(env, tree, fd, stdout);
	close(fd[0]);
	waitpid(pipe1, NULL, 0);
	waitpid(pipe2, &wstatus, 0);
	if (WIFEXITED(wstatus))
		env->exit_status = WEXITSTATUS(wstatus);
}

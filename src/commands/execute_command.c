/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:10:00 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/07 12:59:41 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execve(t_env *env, char **argv)
{
	char	*path;

	path = ft_get_cmd_path(argv[0], env->path);
	execve(path, argv, env->envp);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (access(path, F_OK) != 0)
	{
		ft_command_error(argv[0]);
		exit(exit_cmd_not_found);
	}
	ft_perm_error(argv[0]);
	exit(exit_cant_exec);
}

static char	**ft_get_cmd(t_env *env, t_astree *tree)
{
	char	*cmd;
	char	**argv;

	cmd = ft_get_astree_cmd(tree);
	argv = ft_split_args(cmd);
	free(cmd);
	argv = ft_parse_env_variables(env, argv);
	argv = ft_parse_wildcards(argv);
	return (argv);
}

void	ft_execute_command(t_env *env, t_astree *tree, int stdin, int stdout)
{
	int		builtin;
	int		wstatus;
	pid_t	pid;
	char	**argv;

	argv = ft_get_cmd(env, tree);
	builtin = ft_get_builtin(argv[0]);
	if (builtin > 0)
	{
		env->builtins[builtin](env, argv, stdout);
		ft_free_tab(argv);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(stdin, STDIN_FILENO);
		dup2(stdout, STDOUT_FILENO);
		ft_execve(env, argv);
	}
	ft_free_tab(argv);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		env->exit_status = WEXITSTATUS(wstatus);
}

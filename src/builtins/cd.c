/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:20:29 by aquincho          #+#    #+#             */
/*   Updated: 2022/12/05 10:43:41 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_home(t_env *env)
{
	char	*path;
	int		i;

	i = 0;
	while (env->envp[i] && ft_strncmp(env->envp[i], "HOME=", 5))
		i++;
	if (!env->envp[i])
		path = ft_strdup(".");
	path = env->envp[i];
	path = ft_strchr(path, '=') + 1;
	return (path);
}

void	ft_cd(t_env *env, char **argv, int stdout)
{
	char	*path;

	(void)stdout;
	if (!argv[1])
		path = ft_find_home(env);
	else if (argv[1] && argv[2])
	{
		printf("minishell: cd: Too many arguments\n");
		env->exit_status = EXIT_FAILURE;
		return ;
	}
	else
		path = argv[1];
	if (chdir(path) < 0)
	{
		path = ft_strjoin("minishel: ", path);
		perror(path);
		env->exit_status = EXIT_FAILURE;
	}
	env->exit_status = EXIT_SUCCESS;
}

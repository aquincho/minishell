/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:29:52 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 16:33:31 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, X_OK) == 0)
			return (res);
		free(res);
		++i;
	}
	return (cmd);
}

static int	ft_parse_path(t_env *env, char *path)
{
	char	*tmp;

	tmp = ft_substr(path, 5, ft_strlen(path));
	if (!tmp)
		return (EXIT_FAILURE);
	env->path = ft_split(tmp, ':');
	free(tmp);
	if (!env->path)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_init_path(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_parse_path(env, envp[i]));
		++i;
	}
	env->path = ft_calloc(1, sizeof(char *));
	if (!env->path)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:02:09 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 16:44:34 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_tab(char **argv, size_t incr)
{
	char	**res;
	size_t	i;

	if (!argv)
		return (ft_calloc(incr + 1, sizeof(char *)));
	i = 0;
	while (argv[i])
		++i;
	res = (char **)ft_calloc(i + incr + 1, sizeof(char *));
	i = 0;
	while (argv[i])
	{
		res[i] = ft_strdup(argv[i]);
		++i;
	}
	return (res);
}

void	ft_env(t_env *env, char **argv, int stdout)
{
	int	i;

	(void)argv;
	i = 0;
	while (env->envp[i])
	{
		ft_putendl_fd(env->envp[i], stdout);
		++i;
	}
	env->exit_status = exit_success;
}

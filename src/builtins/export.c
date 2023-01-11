/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:50:08 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 14:07:51 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_get_tab_len(char **argv)
{
	size_t	i;
	size_t	incr;

	incr = 0;
	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
			++incr;
		++i;
	}
	return (incr);
}

static int	ft_add_env_variable(char **envp, char *arg, int index)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (arg[len] != '=')
		++len;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], arg, len + 1))
		{
			free(envp[i]);
			envp[i] = ft_strdup(arg);
			return (index);
		}
		++i;
	}
	envp[i] = ft_strdup(arg);
	return (i);
}

void	ft_export(t_env *env, char **argv, int stdout)
{
	int		i;
	int		j;
	char	**envp;

	(void)stdout;
	envp = ft_copy_tab(env->envp, ft_get_tab_len(argv));
	i = 0;
	while (envp[i])
		++i;
	j = 1;
	while (argv[j])
	{
		if (ft_strchr(argv[j], '='))
			i = ft_add_env_variable(envp, argv[j], i);
		++j;
	}
	ft_free_tab(env->envp);
	env->envp = envp;
	env->exit_status = exit_success;
}

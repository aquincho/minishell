/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:19:06 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 13:03:15 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_get_tab_len(char **tab)
{
	size_t	len;

	len = 0;
	while (tab[len])
		++len;
	return (len);
}

static int	ft_find_in_env(char **envp, char *arg)
{
	int		i;
	char	**tab;
	char	*var;
	size_t	len;

	tab = ft_split(arg, '=');
	var = tab[0];
	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
		{
			ft_free_tab(tab);
			return (i);
		}
		++i;
	}
	ft_free_tab(tab);
	return (-1);
}

void	ft_unset(t_env *env, char **argv, int stdout)
{
	int		i;
	int		var_index;
	size_t	len;

	(void)stdout;
	len = ft_get_tab_len(env->envp);
	i = 1;
	while (argv[i])
	{
		var_index = ft_find_in_env(env->envp, argv[i]);
		if (var_index >= 0)
		{
			free(env->envp[var_index]);
			env->envp[var_index] = env->envp[len - 1];
			env->envp[len - 1] = NULL;
			--len;
		}
		++i;
	}
}

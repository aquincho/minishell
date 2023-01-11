/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:32:08 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 14:40:07 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_is_env_variable(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] && arg[i + 1] == '\'')
				return (-2);
			return (i);
		}
		++i;
	}
	return (-1);
}

static char	*ft_substitute_variable(t_env *env, char *arg)
{
	int		i;
	char	*var;
	char	**envp;
	size_t	len;

	if (!ft_strncmp(arg, "$?", 2))
		return (ft_itoa(env->exit_status));
	var = ft_strjoin(ft_substr(arg, 1, ft_strlen(arg)), "=");
	len = ft_strlen(var);
	envp = env->envp;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len))
			return (ft_substr(envp[i], len, ft_strlen(envp[i])));
		++i;
	}
	return (ft_strdup(""));
}

static char	*ft_purge_quote(char *arg)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	while (arg[j])
	{
		if (arg[j] == '\'')
			j++;
		if (arg[j])
		{
			tmp[i] = arg [j];
			i++;
			j++;
		}
	}
	tmp[i] = '\0';
	free (arg);
	return (tmp);
}

char	**ft_parse_env_variables(t_env *env, char **argv)
{
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	while (argv[i])
	{
		start = ft_is_env_variable(argv[i]);
		if (start >= 0)
		{
			tmp = ft_substr(argv[i], 0, start);
			argv[i] = ft_strjoin(tmp,
					ft_substitute_variable(env, &argv[i][start]));
		}
		else if (start == -2)
			argv[i] = ft_purge_quote(argv[i]);
		++i;
	}
	return (argv);
}

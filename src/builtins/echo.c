/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:24:55 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 10:43:53 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_check_newline(char *arg)
{
	if (ft_strlen(arg) != 2)
		return (1);
	return (ft_strncmp(arg, "-n", 2));
}

void	ft_echo(t_env *env, char **argv, int stdout)
{
	int	i;
	int	newline;

	newline = ft_check_newline(argv[1]);
	i = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], stdout);
		if (argv[i + 1])
			ft_putstr_fd(" ", stdout);
		++i;
	}
	if (newline)
		ft_putendl_fd("", stdout);
	env->exit_status = exit_success;
}

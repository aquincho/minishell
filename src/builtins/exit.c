/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:28:32 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 17:00:53 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env *env, char **argv, int stdout)
{
	(void)stdout;
	ft_cleanup(env);
	ft_clean_astree(env->tree);
	if (!argv || !argv[1])
		exit(env->exit_status);
	exit(ft_atoi(argv[1]));
}

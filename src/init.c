/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 09:32:06 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 16:51:50 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_env(t_env *env, char **envp)
{
	env->path = NULL;
	env->tree = NULL;
	env->envp = ft_copy_tab(envp, 0);
	if (!env->envp)
		return (EXIT_FAILURE);
	env->exit_status = exit_success;
	env->builtins[0] = ft_echo;
	env->builtins[1] = ft_env;
	env->builtins[2] = ft_export;
	env->builtins[3] = ft_unset;
	env->builtins[4] = ft_exit;
	env->builtins[5] = ft_cd;
	env->builtins[6] = ft_pwd;
	if (ft_init_path(env, envp) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

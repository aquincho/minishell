/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:29:07 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 13:32:31 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_logic(t_env *env, t_astree *tree, int stdin, int stdout)
{
	ft_execute(env, tree->left, stdin, stdout);
	if (tree->token->line[tree->token->start] == '|')
	{
		if (env->exit_status != exit_success)
			ft_execute(env, tree->right, stdin, stdout);
	}
	else if (env->exit_status == exit_success)
		ft_execute(env, tree->right, stdin, stdout);
}

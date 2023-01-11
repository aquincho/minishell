/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:36:47 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 13:28:50 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_env *env, t_astree *tree, int stdin, int stdout)
{
	if (!tree)
		return ;
	if (tree->token->type == command_token)
		ft_execute_command(env, tree, stdin, stdout);
	else if (tree->token->type == pipe_token)
		ft_execute_pipe(env, tree, stdin, stdout);
	else if (tree->token->type == redirection_token)
		ft_execute_redirection(env, tree, stdin, stdout);
	else if (tree->token->type == logical_op_token)
		ft_execute_logic(env, tree, stdin, stdout);
}

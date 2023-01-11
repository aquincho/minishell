/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:35:04 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 14:39:00 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell(t_env *env, char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		ft_exit(env, NULL, STDOUT_FILENO);
	if (line)
	{
		if (*line)
		{
			env->tree = ft_parser(ft_lexer(line));
			if (!env->tree)
			{
				env->exit_status = 127;
				return ;
			}
			ft_execute(env, env->tree, STDIN_FILENO, STDOUT_FILENO);
			ft_clean_astree(env->tree);
		}
		free(line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:30:31 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/03 10:30:36 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_builtin(char *cmd)
{
	int					i;
	size_t				len;
	static const char	*cmds[NB_BUILTINS] = {
		"echo",
		"env",
		"export",
		"unset",
		"exit",
		"cd",
		"pwd"
	};

	i = 0;
	len = ft_strlen(cmd);
	while (i < NB_BUILTINS)
	{
		if (len == ft_strlen(cmds[i]) && !ft_strncmp(cmd, cmds[i], len))
			return (i);
		++i;
	}
	return (-1);
}

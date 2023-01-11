/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:19:09 by aquincho          #+#    #+#             */
/*   Updated: 2022/12/05 15:19:14 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_lines(char *line, char *lim, int fd)
{
	line = readline(">");
	while (line && (ft_strncmp(line, lim, ft_strlen(lim))
			|| ft_strlen(lim) != ft_strlen(line)))
	{
		line = ft_strjoin(line, "\n");
		write(fd, line, ft_strlen(line));
		free (line);
		line = NULL;
		line = readline(">");
	}
	if (line)
		free (line);
}

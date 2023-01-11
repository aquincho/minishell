/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:47:50 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 15:03:12 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_move_forward(char *line, int c, int equal, int start)
{
	if (!equal)
		while (line && line[start] && line[start] != c)
			++start;
	else
		while (line && line[start] && line[start] == c)
			++start;
	if (!line[start])
		return (-1);
	return (start);
}

static int	ft_check_helper(char *line, int start)
{
	if (line[start] == '|' && (!line[start + 1] || line[start + 1] != '|'))
	{
		start = ft_move_forward(line, ' ', 1, start + 1);
		if (start < 0)
			return (start);
	}
	if ((line[start] == '|' && line[start + 1] && line[start + 1] == '|')
		|| (line[start] == '&' && line[start + 1] && line[start + 1] == '&'))
		start = ft_move_forward(line, ' ', 1, start + 2);
	return (start);
}

int	ft_check_miss_item(char *line)
{
	int			open_parenthesis;
	int			start;

	open_parenthesis = 0;
	start = 0;
	while (line && line[start])
	{
		start = ft_check_helper(line, start);
		if (start < 0)
			return (4);
		open_parenthesis += (line[start] == '(');
		if (line[start] == ')')
		{
			if (!open_parenthesis)
			{
				printf("bash: Syntax error near unexpected token )\n");
				return (6);
			}
			open_parenthesis -= (line[start] == ')');
		}
		++start;
	}
	if (open_parenthesis)
		return (5);
	return (0);
}

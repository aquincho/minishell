/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 07:38:24 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/01 07:46:36 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	ft_check_token_type(char *line, int start)
{
	if (line[start] == '|' && (!line[start + 1] || line[start + 1] != '|'))
		return (pipe_token);
	if (line[start] == '>' || line[start] == '<')
		return (redirection_token);
	if ((line[start] == '&' && line[start + 1] && line[start + 1] == '&')
		|| (line[start] == '|' && line[start + 1] && line[start + 1] == '|'))
		return (logical_op_token);
	if (line[start] == '(')
		return (parenthesis_open_token);
	if (line[start] == ')')
		return (parenthesis_close_token);
	return (command_token);
}

static inline int	ft_is_same(char *line, int start, t_token *token)
{
	if (line[start] == ' ')
		return (1);
	return (ft_check_token_type(line, start) == token->type);
}

static inline int	ft_check_quote(char *line, int start)
{
	++start;
	if (line[start] && line[start] == 34)
	{
		++start;
		while (line[start] && line[start] != 34)
			++start;
	}
	if (line[start] && line[start] == 39)
	{
		++start;
		while (line[start] && line[start] != 39)
			++start;
	}
	return (start);
}

unsigned int	ft_get_token_end(char *line, t_token *token)
{
	int	start;

	start = token->start;
	if (token->type == redirection_token)
	{
		while ((line[start]) && (ft_is_same(line, start, token)
				|| line[start] == ' '))
			++(start);
		while (line[start] && line[start] != ' ')
			++(start);
		while (line[start] && line[start] == ' ')
			++(start);
	}
	else if (token->type == logical_op_token)
	{
		start += 2;
		while (line[start] && ft_is_same(line, start, token))
			++start;
	}
	else
		while (line[start] && ft_is_same(line, start, token))
			start = ft_check_quote(line, start);
	return (start);
}

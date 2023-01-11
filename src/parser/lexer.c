/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:15:08 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 14:52:52 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_prompt_item(char *line, int item)
{
	char	*line_read;
	char	*tmp;
	char	*prompt;

	prompt = ">";
	line_read = readline(prompt);
	tmp = ft_strjoin(line, "");
	if (item >= 3 && item <= 4)
		tmp = ft_strjoin(line, " ");
	tmp = ft_strjoin(tmp, line_read);
	line = tmp;
	return (line);
}

static	t_token	*ft_get_token(char *line, unsigned int start)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = ft_check_token_type(line, start);
	token->start = start;
	token->line = line;
	token->end = ft_get_token_end(line, token);
	return (token);
}

static t_list	*ft_parse_tokens(char *line)
{
	t_list			*tokens;
	t_list			*current;
	unsigned int	start;

	tokens = NULL;
	start = 0;
	while (line[start])
	{
		while (line[start] == ' ')
			++start;
		if (!line[start])
			break ;
		current = ft_lstnew(ft_get_token(line, start));
		ft_lstadd_back(&tokens, current);
		start = ((t_token *)current->content)->end;
	}
	return (tokens);
}

t_list	*ft_lexer(char *line)
{
	int	item_miss;

	if (!line || !*line)
		return (0);
	item_miss = ft_check_miss_item(line);
	if (item_miss == 6)
		return (NULL);
	while (item_miss)
	{
		line = ft_prompt_item(line, item_miss);
		item_miss = ft_check_miss_item(line);
	}
	add_history(line);
	return (ft_parse_tokens(line));
}

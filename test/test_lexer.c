/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:49:55 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 14:20:05 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "minishell.h"
/*
static t_token_type	ft_check_type(char c)
{
	if (c == '|')
		return (pipe_token);
	if (c == '>' || c == '<')
		return (redirection_token);
	return (command_token);
}

static inline int	ft_is_same(char c, t_token *token)
{
	if (c == ' ')
		return (1);
	return (ft_check_type(c) == token->type);
}*/

TEST_GROUP(Lexer);

TEST_SETUP(Lexer)
{
}

TEST_TEAR_DOWN(Lexer)
{
}

TEST(Lexer, SingleCommand)
{
	char	*cmd = "cat Makefile";
	t_list	*tokens;
	t_token	*valid;

	valid = (t_token *)malloc(sizeof(t_token));
	valid->type = command_token;
	valid->line = cmd;
	valid->start = 0;
	valid->end = ft_strlen(cmd);

	tokens = ft_lexer(cmd);
	TEST_ASSERT_EQUAL_MEMORY(valid, tokens->content, sizeof(valid));
}

TEST(Lexer, SingleRedirection)
{
	char	*cmd = " >> ";
	t_list	*tokens;
	t_token	*valid;

	valid = (t_token *)malloc(sizeof(t_token));
	valid->type = redirection_token;
	valid->line = cmd;
	valid->start = 1;
	valid->end = ft_strlen(cmd);

	tokens = ft_lexer(cmd);
	TEST_ASSERT_EQUAL_MEMORY(valid, tokens->content, sizeof(valid));
}

TEST(Lexer, DoubleRedirection)
{
	char	*cmd = "<< infile ";
	t_list	*tokens;
	t_token	*valid;

	valid = (t_token *)malloc(sizeof(t_token));
	valid->type  = redirection_token;
	valid->line = cmd;
	valid->start = 0;
	valid->end = ft_strlen(cmd);

	tokens = ft_lexer(cmd);
	TEST_ASSERT_EQUAL_MEMORY(valid, tokens->content, sizeof(valid));
	TEST_ASSERT_EQUAL_INT(valid->type, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_INT(valid->start, ((t_token *)tokens->content)->start);
	TEST_ASSERT_EQUAL_INT(valid->end, ((t_token *)tokens->content)->end);
}

TEST(Lexer, OpenParenthesis)
{
	char	*cmd = "()";
	t_list	*tokens;
	t_token	*valid1;
	t_token	*valid2;

	valid1 = (t_token *)malloc(sizeof(t_token));
	valid1->type = parenthesis_open_token;
	valid1->line = cmd;
	valid1->start = 0;
	valid1->end = 1;
	valid2 = (t_token *)malloc(sizeof(t_token));
	valid2->type = parenthesis_close_token;
	valid2->line = cmd;
	valid2->start = 1;
	valid2->end = 2;

	tokens = ft_lexer(cmd);
	TEST_ASSERT_EQUAL_INT(valid1->type, ((t_token *)tokens->content)->type);
	TEST_ASSERT_EQUAL_INT(valid1->start, ((t_token *)tokens->content)->start);
	TEST_ASSERT_EQUAL_INT(valid1->end, ((t_token *)tokens->content)->end);
	TEST_ASSERT_EQUAL_INT(valid2->type, ((t_token *)tokens->next->content)->type);
	TEST_ASSERT_EQUAL_INT(valid2->start, ((t_token *)tokens->next->content)->start);
	TEST_ASSERT_EQUAL_INT(valid2->end, ((t_token *)tokens->next->content)->end);
}

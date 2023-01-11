/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:16:47 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 16:44:25 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "minishell.h"

TEST_GROUP(Parser);

TEST_SETUP(Parser)
{
}

TEST_TEAR_DOWN(Parser)
{
}

static int	ft_cmp_astree(t_astree *t1, t_astree *t2)
{
	if ((!t1 && t2) || (t1 && !t2))
		return (0);
	if (!t1 && !t2)
		return (1);
	if (t1->token->line != t2->token->line)
		return (0);
	if (t1->token->start != t2->token->start)
		return (0);
	if (t1->token->end != t2->token->end)
		return (0);
	if (t1->token->type != t2->token->type)
		return (0);
	return (ft_cmp_astree(t1->left, t2->left) && ft_cmp_astree(t1->right, t2->right));
}

TEST(Parser, SingleCommand)
{
	char		*cmd = "cat -e Makefile";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, CommandPipe)
{
	char		*cmd = "cat -e Makefile | grep NAME";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->content);
	valid->left = ft_create_astnode(tokens->content);
	valid->right = ft_create_astnode(tokens->next->next->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, MultiplePipe)
{
	char		*cmd = "cat Makefile | grep $NAME | wc -l";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->content);
	valid->left = ft_create_astnode(tokens->content);
	valid->right = ft_create_astnode(tokens->next->next->next->content);
	valid->right->left = ft_create_astnode(tokens->next->next->content);
	valid->right->right = ft_create_astnode(tokens->next->next->next->next->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, PipeLeftRedirection)
{
	char		*cmd = "< Makefile cat -e | < infile grep NAME";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->next->content);
	valid->left = ft_create_astnode(tokens->content);
	valid->right = ft_create_astnode(tokens->next->next->next->content);
	valid->left->left = ft_create_astnode(tokens->next->content);
	valid->right->left = ft_create_astnode(tokens->next->next->next->next->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, PipeLeftRightRedirection)
{
	char		*cmd = "cat -e < Makefile | > outfile grep src";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->next->content);
	valid->left = ft_create_astnode(tokens->next->content);
	valid->left->left = ft_create_astnode(tokens->content);
	valid->right = ft_create_astnode(tokens->next->next->next->content);
	valid->right->left = ft_create_astnode(tokens->next->next->next->next->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, MultiplePipesRedirections)
{
	char		*cmd = "> logs cat -e < Makefile | grep NAME < infile | < tfile wc -l > outfile";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->next->next->content);
	valid->left = ft_create_astnode(tokens->content);
	valid->left->left = ft_create_astnode(tokens->next->next->content);
	valid->left->left->left = ft_create_astnode(tokens->next->content);
	valid->right = ft_create_astnode(tokens->next->next->next->next->next->next->content);
	valid->right->left = ft_create_astnode(tokens->next->next->next->next->next->content);
	valid->right->left->left = ft_create_astnode(tokens->next->next->next->next->content);
	valid->right->right = ft_create_astnode(tokens->next->next->next->next->next->next->next->content);
	valid->right->right->left = ft_create_astnode(tokens->next->next->next->next->next->next->next->next->next->content);
	valid->right->right->left->left = ft_create_astnode(tokens->next->next->next->next->next->next->next->next->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, PipeRedirectionNoCmd)
{
	char		*cmd = "cat -e Makefile | > log";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->content);
	valid->left = ft_create_astnode(tokens->content);
	valid->right = ft_create_astnode(tokens->next->next->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, MultipleRedirection)
{
	char		*cmd = "cat -e > out < Makefile";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->content);
	valid->left = ft_create_astnode(tokens->next->next->content);
	valid->left->left = ft_create_astnode(tokens->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, SingleParenthese)
{
	char		*cmd = "(cat Makefile || ls) && echo cc";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->next->next->next->next->content);
	valid->left = ft_create_astnode(tokens->next->next->content);
	valid->left->left = ft_create_astnode(tokens->next->content);
	valid->left->right = ft_create_astnode(tokens->next->next->next->content);
	valid->right = ft_create_astnode(tokens->next->next->next->next->next->next->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

TEST(Parser, UselessParenthese)
{
	char		*cmd = "cat Makefile || (ls && echo cc)";
	t_list		*tokens;
	t_astree	*valid;
	t_astree	*res;

	tokens = ft_lexer(cmd);
	valid = ft_create_astnode(tokens->next->content);
	valid->left = ft_create_astnode(tokens->content);
	valid->right = ft_create_astnode(tokens->next->next->next->next->content);
	valid->right->left = ft_create_astnode(tokens->next->next->next->content);
	valid->right->right = ft_create_astnode(tokens->next->next->next->next->next->content);
	res = ft_parser(tokens);
	TEST_ASSERT_TRUE(ft_cmp_astree(valid, res));
}

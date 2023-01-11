/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:41:24 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/02 10:49:38 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "minishell.h"

TEST_GROUP(Args);

TEST_SETUP(Args)
{
}

TEST_TEAR_DOWN(Args)
{
}

TEST(Args, NoArg)
{
	char	**argv;
	char	*cmd;


	cmd = "";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[0]);
}

TEST(Args, EmptySingleQuoteNoArg)
{
	char	**argv;
	char	*cmd;


	cmd = "\'\'";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("", argv[0]);
}

TEST(Args, EmptyDoubleQuoteNoArg)
{
	char	**argv;
	char	*cmd;


	cmd = "\"\"";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("", argv[0]);
}

TEST(Args, WhiteSpaceNoArg)
{
	char	**argv;
	char	*cmd;


	cmd = "";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[0]);
}

TEST(Args, SingleCmd)
{
	char	**argv;
	char	*cmd;


	cmd = "ls";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("ls", argv[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[1]);
}

TEST(Args, WhiteSpaceSingleCmd)
{
	char	**argv;
	char	*cmd;


	cmd = "   ls   ";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("ls", argv[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[1]);
}

TEST(Args, SingleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "cat \'123   789\'";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[2]);
}

TEST(Args, WhiteSpaceSingleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "cat      \'123   789\'     ";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[2]);
}

TEST(Args, DoubleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "cat \"123   789\"";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[2]);
}

TEST(Args, WhiteSpaceDoubleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "cat      \"123   789\"    ";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[2]);
}

TEST(Args, SingleDoubleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "cat \'123   789\' \"123   789\"";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[1]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[2]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[3]);
}

TEST(Args, WhiteSpaceSingleDoubleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "   cat    \'123   789\'    \"123   789\"   ";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[1]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[2]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[3]);
}

TEST(Args, DoubleSingleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "cat \"123   789\" \'123   789\'";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[1]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[2]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[3]);
}

TEST(Args, WhiteSpaceDoubleSingleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "   cat    \"123   789\"    \'123   789\'   ";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[1]);
	TEST_ASSERT_EQUAL_STRING("123   789", argv[2]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[3]);
}

TEST(Args, InsideSingleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "cat  abc\'123   789\'def";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("abc123   789def", argv[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[2]);
}

TEST(Args, InsideDoubleQuote)
{
	char	**argv;
	char	*cmd;


	cmd = "cat  abc\"123   789\"def";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("abc123   789def", argv[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[2]);
}

TEST(Args, MixAll)
{
	char	**argv;
	char	*cmd;


	cmd = "cat hello abc\'123   789def\' \'\' \"\" world \' \'  \" \" abc\"123   789\"def yy\'   \' zz\"   \"";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("hello", argv[1]);
	TEST_ASSERT_EQUAL_STRING("abc123   789def", argv[2]);
	TEST_ASSERT_EQUAL_STRING("", argv[3]);
	TEST_ASSERT_EQUAL_STRING("", argv[4]);
	TEST_ASSERT_EQUAL_STRING("world", argv[5]);
	TEST_ASSERT_EQUAL_STRING(" ", argv[6]);
	TEST_ASSERT_EQUAL_STRING(" ", argv[7]);
	TEST_ASSERT_EQUAL_STRING("abc123   789def", argv[8]);
	TEST_ASSERT_EQUAL_STRING("yy   ", argv[9]);
	TEST_ASSERT_EQUAL_STRING("zz   ", argv[10]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[11]);
}

TEST(Args, WhiteSpaceMixAll)
{
	char	**argv;
	char	*cmd;


	cmd = "   cat    hello    abc\'123   789def\'    \'\'    \"\"    world   \' \'   \" \"    abc\"123   789\"def   yy\'   \'    zz\"   \"    ";
	argv = ft_split_args(cmd);
	TEST_ASSERT_EQUAL_STRING("cat", argv[0]);
	TEST_ASSERT_EQUAL_STRING("hello", argv[1]);
	TEST_ASSERT_EQUAL_STRING("abc123   789def", argv[2]);
	TEST_ASSERT_EQUAL_STRING("", argv[3]);
	TEST_ASSERT_EQUAL_STRING("", argv[4]);
	TEST_ASSERT_EQUAL_STRING("world", argv[5]);
	TEST_ASSERT_EQUAL_STRING(" ", argv[6]);
	TEST_ASSERT_EQUAL_STRING(" ", argv[7]);
	TEST_ASSERT_EQUAL_STRING("abc123   789def", argv[8]);
	TEST_ASSERT_EQUAL_STRING("yy   ", argv[9]);
	TEST_ASSERT_EQUAL_STRING("zz   ", argv[10]);
	TEST_ASSERT_EQUAL_STRING(NULL, argv[11]);
}

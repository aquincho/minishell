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

TEST_GROUP(Env);

TEST_SETUP(Env)
{
}

TEST_TEAR_DOWN(Env)
{
}

TEST(Env, NoEnvp)
{
	char	**argv;
	char	**valid;
	t_env	env;

	env.envp = ft_calloc(6, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=/usr/bin:/usr/sbin");
	env.envp[1] = ft_strdup("TESTING=coucou");
	env.envp[2] = ft_strdup("TEST=salut");
	env.envp[3] = ft_strdup("NOVALUE=");
	env.envp[4] = ft_strdup("EMPTY");

	env.envp[0] = NULL;
	argv = ft_calloc(4, sizeof(char *));
	valid = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("cat");
	argv[1] = ft_strdup("makefile");
	argv[2] = ft_strdup("$PATH");
	valid[0] = ft_strdup("cat");
	valid[1] = ft_strdup("makefile");
	valid[2] = ft_strdup("");
	argv = ft_parse_env_variables(&env, argv);
	for (int i = 0; argv[i]; ++i)
		TEST_ASSERT_EQUAL_STRING(argv[i], valid[i]);
}

TEST(Env, PathVariable)
{
	char	**argv;
	char	**valid;
	t_env	env;

	env.envp = ft_calloc(6, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=/usr/bin:/usr/sbin");
	env.envp[1] = ft_strdup("TESTING=coucou");
	env.envp[2] = ft_strdup("TEST=salut");
	env.envp[3] = ft_strdup("NOVALUE=");
	env.envp[4] = ft_strdup("EMPTY");

	argv = ft_calloc(4, sizeof(char *));
	valid = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("cat");
	argv[1] = ft_strdup("makefile");
	argv[2] = ft_strdup("$PATH");
	valid[0] = ft_strdup("cat");
	valid[1] = ft_strdup("makefile");
	valid[2] = ft_strdup("/usr/bin:/usr/sbin");
	argv = ft_parse_env_variables(&env, argv);
	for (int i = 0; argv[i]; ++i)
		TEST_ASSERT_EQUAL_STRING(argv[i], valid[i]);
}

TEST(Env, EmptyVariable)
{
	char	**argv;
	char	**valid;
	t_env	env;

	env.envp = ft_calloc(6, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=/usr/bin:/usr/sbin");
	env.envp[1] = ft_strdup("TESTING=coucou");
	env.envp[2] = ft_strdup("TEST=salut");
	env.envp[3] = ft_strdup("NOVALUE=");
	env.envp[4] = ft_strdup("EMPTY");

	argv = ft_calloc(4, sizeof(char *));
	valid = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("cat");
	argv[1] = ft_strdup("makefile");
	argv[2] = ft_strdup("$NOVALUE");
	valid[0] = ft_strdup("cat");
	valid[1] = ft_strdup("makefile");
	valid[2] = ft_strdup("");
	argv = ft_parse_env_variables(&env, argv);
	for (int i = 0; argv[i]; ++i)
		TEST_ASSERT_EQUAL_STRING(argv[i], valid[i]);
}

TEST(Env, InvalidVariable)
{
	char	**argv;
	char	**valid;
	t_env	env;

	env.envp = ft_calloc(6, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=/usr/bin:/usr/sbin");
	env.envp[1] = ft_strdup("TESTING=coucou");
	env.envp[2] = ft_strdup("TEST=salut");
	env.envp[3] = ft_strdup("NOVALUE=");
	env.envp[4] = ft_strdup("EMPTY");

	argv = ft_calloc(4, sizeof(char *));
	valid = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("cat");
	argv[1] = ft_strdup("makefile");
	argv[2] = ft_strdup("$IDONTEXIST");
	valid[0] = ft_strdup("cat");
	valid[1] = ft_strdup("makefile");
	valid[2] = ft_strdup("");
	argv = ft_parse_env_variables(&env, argv);
	for (int i = 0; argv[i]; ++i)
		TEST_ASSERT_EQUAL_STRING(argv[i], valid[i]);
}

TEST(Env, MultipleVariable)
{
	char	**argv;
	char	**valid;
	t_env	env;

	env.envp = ft_calloc(6, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=/usr/bin:/usr/sbin");
	env.envp[1] = ft_strdup("TESTING=coucou");
	env.envp[2] = ft_strdup("TEST=salut");
	env.envp[3] = ft_strdup("NOVALUE=");
	env.envp[4] = ft_strdup("EMPTY");

	argv = ft_calloc(6, sizeof(char *));
	valid = ft_calloc(6, sizeof(char *));
	argv[0] = ft_strdup("cat");
	argv[1] = ft_strdup("makefile");
	argv[2] = ft_strdup("$NOVALUE");
	argv[3] = ft_strdup("$TEST");
	argv[4] = ft_strdup("$TESTING");
	valid[0] = ft_strdup("cat");
	valid[1] = ft_strdup("makefile");
	valid[2] = ft_strdup("");
	valid[3] = ft_strdup("salut");
	valid[4] = ft_strdup("coucou");
	argv = ft_parse_env_variables(&env, argv);
	for (int i = 0; argv[i]; ++i)
		TEST_ASSERT_EQUAL_STRING(argv[i], valid[i]);
}

TEST(Env, InsideVariable)
{
	char	**argv;
	char	**valid;
	t_env	env;

	env.envp = ft_calloc(6, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=/usr/bin:/usr/sbin");
	env.envp[1] = ft_strdup("TESTING=coucou");
	env.envp[2] = ft_strdup("TEST=salut");
	env.envp[3] = ft_strdup("NOVALUE=");
	env.envp[4] = ft_strdup("EMPTY");

	argv = ft_calloc(4, sizeof(char *));
	valid = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("cat");
	argv[1] = ft_strdup("makefile");
	argv[2] = ft_strdup("salut$TESTING");
	valid[0] = ft_strdup("cat");
	valid[1] = ft_strdup("makefile");
	valid[2] = ft_strdup("salutcoucou");
	argv = ft_parse_env_variables(&env, argv);
	for (int i = 0; argv[i]; ++i)
		TEST_ASSERT_EQUAL_STRING(argv[i], valid[i]);
}

TEST(Env, VarCmd)
{
	char	*cmd;
	char	**argv;
	char	**valid;
	t_env	env;

	cmd = "$TESTING";
	env.envp = ft_calloc(6, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=/usr/bin:/usr/sbin");
	env.envp[1] = ft_strdup("TESTING=ls");
	env.envp[2] = ft_strdup("TEST=salut");
	env.envp[3] = ft_strdup("NOVALUE=");
	env.envp[4] = ft_strdup("EMPTY");

	valid = ft_calloc(2, sizeof(char *));
	valid[0] = ft_strdup("ls");
	argv = ft_split_args(cmd);
	argv = ft_parse_env_variables(&env, argv);
	TEST_ASSERT_EQUAL_STRING(argv[0], valid[0]);
}

TEST(Env, VarCmdQuotes)
{
	char	*cmd;
	char	**argv;
	char	**valid;
	t_env	env;

	cmd = "$TESTING \'$TEST\' \"$TEST\"";
	env.envp = ft_calloc(6, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=/usr/bin:/usr/sbin");
	env.envp[1] = ft_strdup("TESTING=ls");
	env.envp[2] = ft_strdup("TEST=salut");
	env.envp[3] = ft_strdup("NOVALUE=");
	env.envp[4] = ft_strdup("EMPTY");

	valid = ft_calloc(4, sizeof(char *));
	valid[0] = ft_strdup("ls");
	valid[1] = ft_strdup("salut");
	valid[2] = ft_strdup("ls");
	argv = ft_split_args(cmd);
	argv = ft_parse_env_variables(&env, argv);
	TEST_ASSERT_EQUAL_STRING(argv[0], valid[0]);
}
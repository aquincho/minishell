/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 09:34:34 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 14:39:30 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "minishell.h"

TEST_GROUP(Path);

TEST_SETUP(Path)
{
}

TEST_TEAR_DOWN(Path)
{
}

TEST(Path, NoEnvp)
{
	t_env	env;

	TEST_ASSERT_TRUE(ft_init_env(&env, NULL) == EXIT_SUCCESS);
	TEST_ASSERT_TRUE(env.path);
	TEST_ASSERT_TRUE(env.path[0] == NULL);
}

TEST(Path, NoPath)
{
	t_env	env;
	char	**envp;

	envp = ft_calloc(3, sizeof(char *));
	envp[0] = ft_strdup("MYPATH=yolo");
	envp[1] = ft_strdup("NOTAPATH=test");
	TEST_ASSERT_TRUE(ft_init_env(&env, envp) == EXIT_SUCCESS);
	TEST_ASSERT_TRUE(env.path);
	TEST_ASSERT_TRUE(env.path[0] == NULL);
}

TEST(Path, SinglePath)
{
	t_env	env;
	char	**envp;

	envp = ft_calloc(3, sizeof(char *));
	envp[0] = ft_strdup("MYPATH=yolo");
	envp[1] = ft_strdup("PATH=test");
	TEST_ASSERT_TRUE(ft_init_env(&env, envp) == EXIT_SUCCESS);
	TEST_ASSERT_TRUE(env.path);
	TEST_ASSERT_EQUAL_STRING(env.path[0], "test");
	TEST_ASSERT_TRUE(env.path[1] == NULL);
}

TEST(Path, MultiplePath)
{
	t_env	env;
	char	**envp;

	envp = ft_calloc(6, sizeof(char *));
	envp[0] = ft_strdup("MYPATH=yolo");
	envp[1] = ft_strdup("NOTAPATH=test");
	envp[2] = ft_strdup("CMD=cat/echo");
	envp[3] = ft_strdup("Still Not a PAth");
	envp[4] = ft_strdup("PATH=test1:test2:test3");
	TEST_ASSERT_TRUE(ft_init_env(&env, envp) == EXIT_SUCCESS);
	TEST_ASSERT_TRUE(env.path);
	TEST_ASSERT_EQUAL_STRING(env.path[0], "test1");
	TEST_ASSERT_EQUAL_STRING(env.path[1], "test2");
	TEST_ASSERT_EQUAL_STRING(env.path[2], "test3");
	TEST_ASSERT_TRUE(env.path[3] == NULL);
}

TEST(Path, EmptyPath)
{
	t_env	env;
	char	**envp;

	envp = ft_calloc(3, sizeof(char *));
	envp[0] = ft_strdup("MYPATH=yolo");
	envp[1] = ft_strdup("PATH=");
	TEST_ASSERT_TRUE(ft_init_env(&env, envp) == EXIT_SUCCESS);
	TEST_ASSERT_TRUE(env.path);
	TEST_ASSERT_TRUE(env.path[0] == NULL);
}

TEST(Path, CmdNoPath)
{
	char	**path;

	path = ft_calloc(1, sizeof(char *));
	TEST_ASSERT_EQUAL_STRING(ft_get_cmd_path("cat", path), "cat");
}

TEST(Path, NoCmdPath)
{
	char	**path;

	path = ft_calloc(3, sizeof(char *));
	path[0] = ft_strdup("/usr/bin");
	path[1] = ft_strdup("/bin");
	TEST_ASSERT_EQUAL_STRING(ft_get_cmd_path("idontexist", path), "idontexist");
}

TEST(Path, CmdPath)
{
	char	**path;

	path = ft_calloc(4, sizeof(char *));
	path[0] = ft_strdup("/usr/bin");
	path[1] = ft_strdup("/bin");
	path[2] = ft_strdup(".");
	open("mycmd", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	TEST_ASSERT_EQUAL_STRING(ft_get_cmd_path("mycmd", path), "./mycmd");
	unlink("mycmd");
}

TEST(Path, CmdNoRights)
{
	char	**path;

	path = ft_calloc(4, sizeof(char *));
	path[0] = ft_strdup("/usr/bin");
	path[1] = ft_strdup("/bin");
	path[2] = ft_strdup(".");
	open("mycmd", O_CREAT | O_WRONLY | O_TRUNC, 0);
	TEST_ASSERT_EQUAL_STRING(ft_get_cmd_path("mycmd", path), "mycmd");
	unlink("mycmd");
}

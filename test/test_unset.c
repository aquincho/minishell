/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:06:54 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 10:50:14 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "minishell.h"

TEST_GROUP(Unset);

TEST_SETUP(Unset)
{
}

TEST_TEAR_DOWN(Unset)
{
}

static int	ft_find_env(char **envp, char *arg)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(arg);
	while (envp[i])
	{
		if (len == ft_strlen(envp[i]) && !ft_strncmp(envp[i], arg, len))
			return (1);
		++i;
	}
	return (0);
}

TEST(Unset, NoEnv)
{
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(1, sizeof(char *));
	argv = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup("unset");
	argv[1] = ft_strdup("TEST=success");
	ft_unset(&env, argv, STDOUT_FILENO);
	TEST_ASSERT_TRUE(!ft_find_env(env.envp, argv[1]));
}

TEST(Unset, SingleCommand)
{
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(3, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=whatever");
	env.envp[1] = ft_strdup("YOLO=swag");
	argv = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup("unset");
	argv[1] = ft_strdup("YOLO=swag");
	ft_unset(&env, argv, STDOUT_FILENO);
	TEST_ASSERT_TRUE(!ft_find_env(env.envp, argv[1]));
	TEST_ASSERT_TRUE(ft_find_env(env.envp, "PATH=whatever"));
}

TEST(Unset, MultipleCommand)
{
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(5, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=whatever");
	env.envp[1] = ft_strdup("YOLO=swag");
	env.envp[2] = ft_strdup("YOLOS=toto");
	env.envp[3] = ft_strdup("MY=var");
	argv = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("unset");
	argv[1] = ft_strdup("YOLO=swag");
	argv[2] = ft_strdup("MY=var");
	ft_unset(&env, argv, STDOUT_FILENO);
	TEST_ASSERT_TRUE(!ft_find_env(env.envp, argv[1]));
	TEST_ASSERT_TRUE(!ft_find_env(env.envp, argv[2]));
	TEST_ASSERT_TRUE(ft_find_env(env.envp, "PATH=whatever"));
	TEST_ASSERT_TRUE(ft_find_env(env.envp, "YOLOS=toto"));
}

TEST(Unset, CmdNotFound)
{
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(5, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=whatever");
	env.envp[1] = ft_strdup("YOLO=swag");
	env.envp[2] = ft_strdup("YOLOS=toto");
	env.envp[3] = ft_strdup("MY=var");
	argv = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup("unset");
	argv[1] = ft_strdup("YOL=swag");
	ft_unset(&env, argv, STDOUT_FILENO);
	TEST_ASSERT_TRUE(!ft_find_env(env.envp, argv[1]));
	TEST_ASSERT_TRUE(ft_find_env(env.envp, "PATH=whatever"));
	TEST_ASSERT_TRUE(ft_find_env(env.envp, "YOLOS=toto"));
	TEST_ASSERT_TRUE(ft_find_env(env.envp, "YOLO=swag"));
	TEST_ASSERT_TRUE(ft_find_env(env.envp, "MY=var"));
}

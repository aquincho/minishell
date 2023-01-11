/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:38:54 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 14:40:18 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "minishell.h"

TEST_GROUP(Export);

TEST_SETUP(Export)
{
}

TEST_TEAR_DOWN(Export)
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

TEST(Export, NoEnv)
{
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(1, sizeof(char *));
	argv = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup("export");
	argv[1] = ft_strdup("TEST=SUCCESS");
	ft_export(&env, argv, STDOUT_FILENO);
	TEST_ASSERT_TRUE(ft_find_env(env.envp, argv[1]));
}

TEST(Export, SingleVariable)
{
	char	**envp;
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(5, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=whatever");
	env.envp[1] = ft_strdup("YOLO=swag");
	env.envp[2] = ft_strdup("TEST=success??");
	env.envp[3] = ft_strdup("TOTO=toto");
	envp = ft_calloc(5, sizeof(char *));
	envp[0] = ft_strdup("PATH=whatever");
	envp[1] = ft_strdup("YOLO=swag");
	envp[2] = ft_strdup("TEST=success??");
	envp[3] = ft_strdup("TOTO=toto");
	argv  = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup("export");
	argv[1] = ft_strdup("ARGV=1");
	ft_export(&env, argv, STDOUT_FILENO);
	TEST_ASSERT_TRUE(ft_find_env(env.envp, argv[1]));
	for (int i = 0; envp[i]; ++i)
		TEST_ASSERT_TRUE(ft_find_env(env.envp, envp[i]));
}

TEST(Export, MultipleVariable)
{
	char	**envp;
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(5, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=whatever");
	env.envp[1] = ft_strdup("YOLO=swag");
	env.envp[2] = ft_strdup("TEST=success??");
	env.envp[3] = ft_strdup("TOTO=toto");
	envp = ft_calloc(5, sizeof(char *));
	envp[0] = ft_strdup("PATH=whatever");
	envp[1] = ft_strdup("YOLO=swag");
	envp[2] = ft_strdup("TEST=success??");
	envp[3] = ft_strdup("TOTO=toto");
	argv  = ft_calloc(5, sizeof(char *));
	argv[0] = ft_strdup("export");
	argv[1] = ft_strdup("ARGV=1");
	argv[2] = ft_strdup("THIS=that");
	argv[3] = ft_strdup("COUCOU=salut");
	ft_export(&env, argv, STDOUT_FILENO);
	for (int i = 1; argv[i]; ++i)
		TEST_ASSERT_TRUE(ft_find_env(env.envp, argv[i]));
	for (int i = 0; envp[i]; ++i)
		TEST_ASSERT_TRUE(ft_find_env(env.envp, envp[i]));
}

TEST(Export, ExistingVariable)
{
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(5, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=whatever");
	env.envp[1] = ft_strdup("TOTO=toto");
	env.envp[2] = ft_strdup("TEST=success??");
	env.envp[3] = ft_strdup("YOLO=swag");
	argv  = ft_calloc(4, sizeof(char *));
	argv[0] = ft_strdup("export");
	argv[1] = ft_strdup("ARGV=1");
	argv[2] = ft_strdup("TOTO=notatoto");
	ft_export(&env, argv, STDOUT_FILENO);
	for (int i = 1; argv[i]; ++i)
		TEST_ASSERT_TRUE(ft_find_env(env.envp, argv[i]));
	TEST_ASSERT_TRUE(!ft_find_env(env.envp, "TOTO=toto"));
}

TEST(Export, NoValue)
{
	char	**envp;
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(5, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=whatever");
	env.envp[1] = ft_strdup("YOLO=swag");
	env.envp[2] = ft_strdup("TEST=success??");
	env.envp[3] = ft_strdup("TOTO=toto");
	envp = ft_calloc(5, sizeof(char *));
	envp[0] = ft_strdup("PATH=whatever");
	envp[1] = ft_strdup("YOLO=swag");
	envp[2] = ft_strdup("TEST=success??");
	envp[3] = ft_strdup("TOTO=toto");
	argv  = ft_calloc(5, sizeof(char *));
	argv[0] = ft_strdup("export");
	argv[1] = ft_strdup("ARGV=");
	argv[2] = ft_strdup("THIS=that");
	argv[3] = ft_strdup("COUCOU=");
	ft_export(&env, argv, STDOUT_FILENO);
	for (int i = 1; argv[i]; ++i)
		TEST_ASSERT_TRUE(ft_find_env(env.envp, argv[i]));
	for (int i = 0; envp[i]; ++i)
		TEST_ASSERT_TRUE(ft_find_env(env.envp, envp[i]));
}

TEST(Export, NoEqual)
{
	char	**envp;
	char	**argv;
	t_env	env;

	env.envp = ft_calloc(5, sizeof(char *));
	env.envp[0] = ft_strdup("PATH=whatever");
	env.envp[1] = ft_strdup("YOLO=swag");
	env.envp[2] = ft_strdup("TEST=success??");
	env.envp[3] = ft_strdup("TOTO=toto");
	envp = ft_calloc(5, sizeof(char *));
	envp[0] = ft_strdup("PATH=whatever");
	envp[1] = ft_strdup("YOLO=swag");
	envp[2] = ft_strdup("TEST=success??");
	envp[3] = ft_strdup("TOTO=toto");
	argv  = ft_calloc(5, sizeof(char *));
	argv[0] = ft_strdup("export");
	argv[1] = ft_strdup("ARGV");
	argv[2] = ft_strdup("THIS");
	argv[3] = ft_strdup("COUCOU");
	ft_export(&env, argv, STDOUT_FILENO);
	for (int i = 1; argv[i]; ++i)
		TEST_ASSERT_TRUE(!ft_find_env(env.envp, argv[i]));
	for (int i = 0; envp[i]; ++i)
		TEST_ASSERT_TRUE(ft_find_env(env.envp, envp[i]));
}

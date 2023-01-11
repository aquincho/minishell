/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:58:38 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 10:06:46 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

static void	run_all_tests(void)
{
	RUN_TEST_GROUP(Lexer);
	RUN_TEST_GROUP(Parser);
	RUN_TEST_GROUP(Path);
	RUN_TEST_GROUP(Env);
	RUN_TEST_GROUP(Export);
	RUN_TEST_GROUP(Unset);
	RUN_TEST_GROUP(Args);
	RUN_TEST_GROUP(Wildcard);
}

int	main(int argc, const char *argv[])
{
	return (UnityMain(argc, argv, run_all_tests));
}

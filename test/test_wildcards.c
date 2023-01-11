/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:59:19 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 10:23:16 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "minishell.h"

TEST_GROUP(Wildcard);

TEST_SETUP(Wildcard)
{
}

TEST_TEAR_DOWN(Wildcard)
{
}

TEST(Wildcard, EndMatch)
{
	char	*pattern = "test*";
	char	*tomatch = "teststring";

	TEST_ASSERT_TRUE(ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, BeginMatch)
{
	char	*pattern = "*test";
	char	*tomatch = "thisisatest";

	TEST_ASSERT_TRUE(ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, MiddleMatch)
{
	char	*pattern = "te*st";
	char	*tomatch = "te42pkpast";

	TEST_ASSERT_TRUE(ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, BeginEndMatch)
{
	char	*pattern = "*test*";
	char	*tomatch = "This_string contains test as substring";

	TEST_ASSERT_TRUE(ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, AllMatch)
{
	char	*pattern = "*yo*lo*";
	char	*tomatch = "Once again you are being matched allover the place";

	TEST_ASSERT_TRUE(ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, EndNoMatch)
{
	char	*pattern = "test*";
	char	*tomatch = "tesstring";

	TEST_ASSERT_TRUE(!ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, BeginNoMatch)
{
	char	*pattern = "*test";
	char	*tomatch = "thisisaTest";

	TEST_ASSERT_TRUE(!ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, MiddleNoMatch)
{
	char	*pattern = "te*st";
	char	*tomatch = "t42pkpast";

	TEST_ASSERT_TRUE(!ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, BeginEndNoMatch)
{
	char	*pattern = "*test*";
	char	*tomatch = "This_string contains no pattern as substring";

	TEST_ASSERT_TRUE(!ft_match_wildcard(pattern, tomatch));
}

TEST(Wildcard, AllNoMatch)
{
	char	*pattern = "*yo*lo*";
	char	*tomatch = "Once again you are being matched all over the place";

	TEST_ASSERT_TRUE(!ft_match_wildcard(pattern, tomatch));
}


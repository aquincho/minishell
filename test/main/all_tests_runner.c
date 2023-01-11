/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_tests_runner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:59:50 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/06 10:23:32 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(Lexer)
{
	RUN_TEST_CASE(Lexer, SingleCommand);
	RUN_TEST_CASE(Lexer, SingleRedirection);
	RUN_TEST_CASE(Lexer, DoubleRedirection);
	RUN_TEST_CASE(Lexer, OpenParenthesis);
}

TEST_GROUP_RUNNER(Parser)
{
	RUN_TEST_CASE(Parser, SingleCommand);
	RUN_TEST_CASE(Parser, CommandPipe);
	RUN_TEST_CASE(Parser, MultiplePipe);
	RUN_TEST_CASE(Parser, PipeLeftRedirection);
	RUN_TEST_CASE(Parser, PipeLeftRightRedirection);
	RUN_TEST_CASE(Parser, MultiplePipesRedirections);
	RUN_TEST_CASE(Parser, PipeRedirectionNoCmd);
	RUN_TEST_CASE(Parser, MultipleRedirection);
	RUN_TEST_CASE(Parser, SingleParenthese);
	RUN_TEST_CASE(Parser, UselessParenthese);
}

TEST_GROUP_RUNNER(Path)
{
	RUN_TEST_CASE(Path, NoEnvp);
	RUN_TEST_CASE(Path, NoPath);
	RUN_TEST_CASE(Path, SinglePath);
	RUN_TEST_CASE(Path, MultiplePath);
	RUN_TEST_CASE(Path, EmptyPath);
	RUN_TEST_CASE(Path, CmdNoPath);
	RUN_TEST_CASE(Path, NoCmdPath);
	RUN_TEST_CASE(Path, CmdPath);
	RUN_TEST_CASE(Path, CmdNoRights);
}

TEST_GROUP_RUNNER(Env)
{
	RUN_TEST_CASE(Env, NoEnvp);
	RUN_TEST_CASE(Env, PathVariable);
	RUN_TEST_CASE(Env, EmptyVariable);
	RUN_TEST_CASE(Env, InvalidVariable);
	RUN_TEST_CASE(Env, MultipleVariable);
	RUN_TEST_CASE(Env, InsideVariable);
	RUN_TEST_CASE(Env, VarCmd);
	RUN_TEST_CASE(Env, VarCmdQuotes);
}

TEST_GROUP_RUNNER(Export)
{
	RUN_TEST_CASE(Export, NoEnv);
	RUN_TEST_CASE(Export, SingleVariable);
	RUN_TEST_CASE(Export, MultipleVariable);
	RUN_TEST_CASE(Export, ExistingVariable);
	RUN_TEST_CASE(Export, NoValue);
	RUN_TEST_CASE(Export, NoEqual);
}

TEST_GROUP_RUNNER(Unset)
{
	RUN_TEST_CASE(Unset, NoEnv);
	RUN_TEST_CASE(Unset, SingleCommand);
	RUN_TEST_CASE(Unset, MultipleCommand);
	RUN_TEST_CASE(Unset, CmdNotFound);
}

TEST_GROUP_RUNNER(Args)
{
	RUN_TEST_CASE(Args, NoArg);
	RUN_TEST_CASE(Args, EmptySingleQuoteNoArg);
	RUN_TEST_CASE(Args, EmptyDoubleQuoteNoArg);
	RUN_TEST_CASE(Args, WhiteSpaceNoArg);
	RUN_TEST_CASE(Args, SingleCmd);
	RUN_TEST_CASE(Args, WhiteSpaceSingleCmd);
	RUN_TEST_CASE(Args, SingleQuote);
	RUN_TEST_CASE(Args, WhiteSpaceSingleQuote);
	RUN_TEST_CASE(Args, DoubleQuote);
	RUN_TEST_CASE(Args, WhiteSpaceDoubleQuote);
	RUN_TEST_CASE(Args, SingleDoubleQuote);
	RUN_TEST_CASE(Args, WhiteSpaceSingleDoubleQuote);
	RUN_TEST_CASE(Args, DoubleSingleQuote);
	RUN_TEST_CASE(Args, WhiteSpaceDoubleSingleQuote);
	RUN_TEST_CASE(Args, InsideSingleQuote);
	RUN_TEST_CASE(Args, InsideDoubleQuote);
	RUN_TEST_CASE(Args, MixAll);
	RUN_TEST_CASE(Args, WhiteSpaceMixAll);
}

TEST_GROUP_RUNNER(Wildcard)
{
	RUN_TEST_CASE(Wildcard, EndMatch);
	RUN_TEST_CASE(Wildcard, BeginMatch);
	RUN_TEST_CASE(Wildcard, MiddleMatch);
	RUN_TEST_CASE(Wildcard, BeginEndMatch);
	RUN_TEST_CASE(Wildcard, AllMatch);
	RUN_TEST_CASE(Wildcard, EndNoMatch);
	RUN_TEST_CASE(Wildcard, BeginNoMatch);
	RUN_TEST_CASE(Wildcard, MiddleNoMatch);
	RUN_TEST_CASE(Wildcard, BeginEndNoMatch);
	RUN_TEST_CASE(Wildcard, AllNoMatch);
}


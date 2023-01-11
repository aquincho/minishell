/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:20:23 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/07 13:02:55 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env		env;
	char		*prompt;
	int			end_sig_flag;
	t_sigaction	action;
	t_sigaction	ignore;

	if (ft_init_env(&env, envp) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	action.sa_sigaction = &ft_sig_handler;
	action.sa_flags = SA_SIGINFO;
	ignore.sa_handler = SIG_IGN;
	ignore.sa_flags = 0;
	if (sigaction(SIGINT, &action, NULL) < 0
		|| sigaction(SIGQUIT, &ignore, NULL) < 0)
	{
		perror ("sigaction");
		return (1);
	}
	end_sig_flag = 0;
	prompt = "prompt:~$";
	while (!end_sig_flag)
		ft_minishell(&env, prompt);
	(void)argc;
	(void)argv;
	return (0);
}

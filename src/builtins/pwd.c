/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:20:41 by aquincho          #+#    #+#             */
/*   Updated: 2022/12/05 10:49:26 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env, char **argv, int stdout)
{
	char	*buff;
	int		i;

	(void)stdout;
	(void)argv;
	errno = 0;
	buff = malloc(BUFF_SIZE * sizeof(char));
	if (!buff)
		exit (EXIT_FAILURE);
	i = 1;
	while (!getcwd(buff, i * BUFF_SIZE) && errno == ERANGE)
	{
		free (buff);
		i++;
		buff = malloc((i * BUFF_SIZE) * sizeof(char));
		errno = 0;
	}
	if (errno && errno != ERANGE)
		exit (EXIT_FAILURE);
	ft_putendl_fd(buff, stdout);
	free(buff);
	env->exit_status = EXIT_SUCCESS;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:07:38 by ple-lez           #+#    #+#             */
/*   Updated: 2022/12/05 12:41:18 by ple-lez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_command_error(char *cmd)
{
	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
}

void	ft_perm_error(char *cmd)
{
	ft_putstr_fd("Permission denied: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
}

void	ft_file_error(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:14:59 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/07 17:15:01 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "executor.h"
#include <stdlib.h>
#include <sys/stat.h>

static void	exit_directory_error(char *path)
{
	if (path[0] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	exec_child_error(char *path)
{
	struct stat	stat_buf;

	if (stat(path, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
		exit_directory_error(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	exit(127);
}

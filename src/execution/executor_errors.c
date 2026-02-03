/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/02/02 00:00:00 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static void	exit_directory_error(char *path)
{
	if (path[0] == '/')
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", path);
		exit(126);
	}
	fprintf(stderr, "minishell: %s: command not found\n", path);
	exit(127);
}

void	exec_child_error(char *path)
{
	struct stat	stat_buf;

	if (stat(path, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
		exit_directory_error(path);
	fprintf(stderr, "minishell: %s: No such file or directory\n", path);
	exit(127);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/01/22 00:00:00 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment/env.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	execute_in_child(t_ast *node, t_env **env, char *path)
{
	if (!path)
	{
		printf("minishell: command not found: %s.\n", node->cmd_args[0]);
		exit(127);
	}
	exec_child(node->cmd_args, path, env);
}

int	execute_forked_command(t_ast *node, t_env **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		reset_child_signals();
		apply_prefix_env(env, node->prefix_env);
		execute_in_child(node, env, get_cmd_path(node->cmd_args[0], *env));
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), -1);
	return (status);
}

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
#include "../utils/utils.h"
#include "executor.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	execute_in_child(t_ast *node, t_minishell *minishell, char *path)
{
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->cmd_args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	exec_child(node->cmd_args, path, minishell);
}

int	execute_forked_command(t_ast *node, t_minishell *minishell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		reset_child_signals();
		apply_prefix_env(minishell, node->prefix_env);
		execute_in_child(node, minishell, get_cmd_path(node->cmd_args[0],
				minishell->env));
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), -1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

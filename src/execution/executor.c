/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:06:20 by radandri          #+#    #+#             */
/*   Updated: 2026/01/19 03:24:39 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment/env.h"
#include "executor.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*get_cmd_path(char *cmd, t_env *env)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	return (find_path(cmd, env));
}

static void	apply_prefix_env(t_env **env, char **prefix_env)
{
	int		i;
	char	*key;
	char	*value;

	if (!prefix_env)
		return ;
	i = 0;
	while (prefix_env[i])
	{
		if (split_key_value_assignment(prefix_env[i], &key, &value) == 0)
		{
			env_set(env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

static void	exec_child(char **cmd_args, char *path, t_env **env)
{
	execve(path, cmd_args, env_to_array(*env));
	perror("execve");
	exit(1);
}

void	reset_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	execute_command(t_ast *node, t_env **env)
{
	pid_t	pid;
	int		status;
	char	*path;
	int		i;
	char	*key;
	char	*value;

	if (!node)
		return (-1);
	if (!node->cmd_args || !node->cmd_args[0])
	{
		if (node->prefix_env)
		{
			i = 0;
			while (node->prefix_env[i])
			{
				if (split_key_value_assignment(node->prefix_env[i],
						&key, &value) == 0)
				{
					env_set(env, key, value);
					free(key);
					free(value);
				}
				i++;
			}
		}
		return (0);
	}
	if (is_builtin(node->cmd_args[0]))
		return (execute_builtin(node, env));
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		reset_child_signals();
		apply_prefix_env(env, node->prefix_env);
		path = get_cmd_path(node->cmd_args[0], *env);
		if (!path)
		{
			printf("minishell: command not found: %s.\n", node->cmd_args[0]);
			exit(127);
		}
		exec_child(node->cmd_args, path, env);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), -1);
	return (status);
}

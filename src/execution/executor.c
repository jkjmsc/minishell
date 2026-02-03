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
#include "../utils/utils.h"
#include "executor.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

char	*get_cmd_path(char *cmd, t_env *env)
{
	struct stat	stat_buf;

	if ((cmd[0] == '/' || cmd[0] == '.') && stat(cmd, &stat_buf) == 0)
		return (cmd);
	return (find_path(cmd, env));
}

void	apply_prefix_env(t_minishell *minishell, char **prefix_env)
{
	int		i;
	char	*key;
	char	*value;
	char	*expanded;

	if (!prefix_env)
		return ;
	i = 0;
	while (prefix_env[i])
	{
		if (split_key_value_assignment(prefix_env[i], &key, &value) == 0)
		{
			expanded = expand_value(value, minishell);
			if (expanded)
			{
				process_compound_assignment(&minishell->env, prefix_env[i], key,
					expanded);
				free(expanded);
			}
			free(key);
			free(value);
		}
		i++;
	}
}

void	exec_child(char **cmd_args, char *path, t_minishell *minishell)
{
	execve(path, cmd_args, env_to_array(minishell->env));
	exec_child_error(path);
}

void	reset_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	execute_command(t_ast *node, t_minishell *minishell)
{
	if (!node)
		return (-1);
	if (!node->cmd_args || !node->cmd_args[0])
	{
		apply_prefix_env(minishell, node->prefix_env);
		return (0);
	}
	if (is_builtin(node->cmd_args[0]))
		return (execute_builtin(node, minishell));
	return (execute_forked_command(node, minishell));
}

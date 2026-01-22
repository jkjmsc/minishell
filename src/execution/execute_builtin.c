/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:03:26 by radandri          #+#    #+#             */
/*   Updated: 2026/01/12 02:53:37 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../builtin/builtin.h"
#include "executor.h"
#include <stdlib.h>

/*
** Count the number of arguments in argv
*/
int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

/*
** Check if a command is a builtin
** Returns 1 if builtin, 0 otherwise
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

/*
** Execute a builtin command
** Returns exit status of the builtin
** Commands: echo, cd, pwd, export, unset, env, exit
*/
int	execute_builtin(t_ast *node, t_env **env)
{
	char	*cmd;

	if (!node || !node->cmd_args || !node->cmd_args[0])
		return (1);
	cmd = node->cmd_args[0];
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (ft_cd(count_argv(node->cmd_args), node->cmd_args, env));
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (ft_echo(node->cmd_args));
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (ft_env(*env));
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_exit(NULL, count_argv(node->cmd_args), node->cmd_args));
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (ft_export(count_argv(node->cmd_args), node->cmd_args, env));
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (ft_unset(node->cmd_args, env));
	return (1);
}

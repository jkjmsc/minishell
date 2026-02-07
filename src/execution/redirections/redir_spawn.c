/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/02/02 12:00:00 by radandri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/executor.h"
#include <signal.h>
#include <unistd.h>

int	apply_redir_to_fd(t_ast *node, int *fd);

static int	apply_all_redirs(t_ast *node, t_ast **cmd_node)
{
	int	fd;
	int	ret;

	if (!node)
		return (-1);
	if (node->type != IN_REDIRECTION && node->type != OUT_REDIRECTION
		&& node->type != APPEND_REDIRECTION)
	{
		*cmd_node = node;
		return (0);
	}
	ret = apply_all_redirs(node->left, cmd_node);
	if (ret < 0)
		return (ret);
	fd = -1;
	ret = apply_redir_to_fd(node, &fd);
	return (ret);
}

void	spawn_redir_child(pid_t *pid, t_ast *node, t_minishell *minishell)
{
	t_ast	*cmd_node;
	int		ret;

	*pid = fork();
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		cmd_node = NULL;
		ret = apply_all_redirs(node, &cmd_node);
		if (ret < 0 || !cmd_node)
			exit(1);
		exit(execute_ast(cmd_node, minishell));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 01:30:00 by radandri          #+#    #+#             */
/*   Updated: 2026/01/19 03:18:06 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/executor.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void	spawn_pipe_child(pid_t *pid, t_pipe_params *p, int unused_fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(p->pipe_fd, p->target_fd) == -1)
			perror("dup2");
		close(p->pipe_fd);
		close(unused_fd);
		exit(execute_ast(p->node, p->minishell));
	}
}

int	wait_pipe_children(pid_t left_pid, pid_t right_pid)
{
	int	status_left;
	int	status_right;

	waitpid(left_pid, &status_left, 0);
	waitpid(right_pid, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	return (1);
}

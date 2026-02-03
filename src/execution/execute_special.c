/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:00:00 by radandri         #+#    #+#             */
/*   Updated: 2026/01/11 01:00:00 by radandri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute_pipe(t_ast *node, t_minishell *minishell)
{
	int				fd[2];
	pid_t			pids[2];
	t_pipe_params	p;

	if (!node || !node->left || !node->right)
		return (1);
	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	p = (t_pipe_params){node->left, minishell, fd[1], STDOUT_FILENO};
	spawn_pipe_child(&pids[0], &p, fd[0]);
	if (pids[0] < 0)
		return (perror("fork"), close(fd[0]), close(fd[1]), 1);
	p = (t_pipe_params){node->right, minishell, fd[0], STDIN_FILENO};
	spawn_pipe_child(&pids[1], &p, fd[1]);
	if (pids[1] < 0)
		return (perror("fork"), close(fd[0]), close(fd[1]), 1);
	close(fd[0]);
	close(fd[1]);
	return (wait_pipe_children(pids[0], pids[1]));
}

void	spawn_redir_child(pid_t *pid, t_ast *node, t_minishell *minishell);

int	execute_redirection(t_ast *node, t_minishell *minishell)
{
	pid_t	pid;
	int		status;

	if (!node || !node->left || !node->right)
		return (1);
	spawn_redir_child(&pid, node, minishell);
	if (pid < 0)
		return (perror("fork"), 1);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_heredoc(t_ast *node, t_minishell *minishell)
{
	int	fd;
	int	saved_stdin;
	int	ret;

	if (!node || !node->right || !node->right->cmd_args
		|| !node->right->cmd_args[0])
		return (1);
	fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open heredoc temp file"), 1);
	write_heredoc_content(fd, node->right->cmd_args[0]);
	close(fd);
	fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (fd < 0)
		return (perror("open heredoc temp file for reading"), 1);
	saved_stdin = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("dup2 heredoc"), close(fd), 1);
	close(fd);
	ret = execute_ast(node->left, minishell);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	unlink("/tmp/heredoc_tmp");
	return (ret);
}

int	execute_ast(t_ast *node, t_minishell *minishell)
{
	if (!node)
		return (0);
	if (node->type == CMD)
		return (execute_command(node, minishell));
	if (node->type == PIPE)
		return (execute_pipe(node, minishell));
	if (node->type == IN_REDIRECTION || node->type == OUT_REDIRECTION
		|| node->type == APPEND_REDIRECTION)
		return (execute_redirection(node, minishell));
	if (node->type == HEREDOC)
		return (execute_heredoc(node, minishell));
	return (1);
}

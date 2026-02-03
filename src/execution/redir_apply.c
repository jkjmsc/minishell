/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/02/02 12:00:00 by radandri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <fcntl.h>
#include <unistd.h>

static int	get_open_flags(t_node_type type)
{
	if (type == IN_REDIRECTION)
		return (O_RDONLY);
	if (type == OUT_REDIRECTION)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	return (O_WRONLY | O_CREAT | O_APPEND);
}

static int	open_redir_file(t_node_type type, char *filename)
{
	int	flags;

	flags = get_open_flags(type);
	if (type == IN_REDIRECTION)
		return (open(filename, flags));
	return (open(filename, flags, 0644));
}

static int	apply_fd_redirect(t_node_type type, int fd)
{
	if (type == IN_REDIRECTION)
		return (dup2(fd, STDIN_FILENO));
	return (dup2(fd, STDOUT_FILENO));
}

int	apply_redir_to_fd(t_ast *node, int *fd)
{
	char	*filename;

	if (!node || !node->right || !node->right->cmd_args
		|| !node->right->cmd_args[0])
		return (-1);
	filename = node->right->cmd_args[0];
	*fd = open_redir_file(node->type, filename);
	if (*fd < 0)
	{
		perror(filename);
		return (-1);
	}
	if (apply_fd_redirect(node->type, *fd) == -1)
	{
		perror("dup2");
		close(*fd);
		return (-1);
	}
	close(*fd);
	return (0);
}

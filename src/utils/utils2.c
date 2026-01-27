/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:04:00 by radandri          #+#    #+#             */
/*   Updated: 2026/01/27 19:42:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenization/token.h"
#include "utils.h"

/*
** Function to handle redirections in the token list before command execution.
** Opens files for redirections and sets file descriptors in the tokens.
** Returns 0 on success, -1 on fatal syntax error that stops execution
*/
int	handle_redirections(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (curr->type == IN_REDIRECTION || curr->type == OUT_REDIRECTION
			|| curr->type == APPEND_REDIRECTION)
		{
			if (open_redir(curr, curr->next) == -1)
				return (-1);
			if (curr->type == OUT_REDIRECTION && curr->next
				&& curr->next->type == PIPE)
				curr = curr->next;
		}
		curr = curr->next;
	}
	return (0);
}

/*
** Function to open a redirection file and set the fd in the redirection token
** Returns 0 on success, -1 on error
*/
static t_token	*get_redir_target(t_token *redir, t_token *filename)
{
	if (redir->type == OUT_REDIRECTION && filename && filename->type == PIPE)
		return (filename->next);
	return (filename);
}

static int	open_redir_file(t_token *redir, const char *path)
{
	int	fd;

	if (redir->type == IN_REDIRECTION)
		fd = open(path, O_RDONLY);
	else if (redir->type == OUT_REDIRECTION)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(path);
		return (-1);
	}
	redir->fd = fd;
	return (0);
}

int	open_redir(t_token *redir, t_token *filename)
{
	t_token	*target;

	if (!filename)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token\n");
		return (-1);
	}
	target = get_redir_target(redir, filename);
	if (!target)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token\n");
		return (-1);
	}
	if (target->type != WORD && target->type != CMD)
	{
		if (redir->type == IN_REDIRECTION)
		{
			fprintf(stderr, "minishell: syntax error near unexpected token\n");
			return (-1);
		}
		fprintf(stderr, "minishell: syntax error near unexpected token\n");
		return (-1);
	}
	return (open_redir_file(redir, target->value));
}

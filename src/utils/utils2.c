/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:04:00 by radandri          #+#    #+#             */
/*   Updated: 2025/12/13 16:06:09 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenization/token.h"
#include "utils.h"

/*
** Function to handle redirections in the token list before command execution.
** Opens files for redirections and sets file descriptors in the tokens.
** Returns 0 on success, -1 on syntax error
*/
int	handle_redirections(t_token *head)
{
	t_token	*curr;
	int		ret;

	curr = head;
	while (curr)
	{
		if (curr->type == IN_REDIRECTION || curr->type == OUT_REDIRECTION
			|| curr->type == APPEND_REDIRECTION)
		{
			ret = open_redir(curr, curr->next);
			if (ret != 0)
				return (ret);
		}
		curr = curr->next;
	}
	return (0);
}

/*
** Function to open a redirection file and set the fd in the redirection token
** Returns 0 on success, -1 on error
*/
int	open_redir(t_token *redir, t_token *filename)
{
	int	fd;

	if (!filename || filename->type != WORD)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token\n");
		return (-2);
	}
	if (redir->type == IN_REDIRECTION)
		fd = open(filename->value, O_RDONLY);
	else if (redir->type == OUT_REDIRECTION)
		fd = open(filename->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename->value);
		return (-1);
	}
	redir->fd = fd;
	return (0);
}

/*
** Close a single token's file descriptor if it is open.
*/
void	close_fd(t_token *token)
{
	if (token && token->fd != -1)
	{
		close(token->fd);
		token->fd = -1;
	}
}

/*
** Close all open file descriptors in a linked list of tokens.
*/
void	close_all_fds(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		close_fd(curr);
		curr = curr->next;
	}
}

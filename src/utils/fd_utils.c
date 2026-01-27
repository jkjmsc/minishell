/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:00:00 by codespace         #+#    #+#             */
/*   Updated: 2026/01/27 20:00:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenization/token.h"

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
